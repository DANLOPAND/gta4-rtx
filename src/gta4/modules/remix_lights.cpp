#include "std_include.hpp"
#include "remix_lights.hpp"

#include "comp_settings.hpp"
#include "game_lights.hpp"
#include "map_settings.hpp"
#include "shared/common/remix_api.hpp"

namespace gta4
{
	const Vector& remix_lights::get_light_position(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return lov && lov->_use_pos ? lov->pos : def.mPosition;
	}

	const Vector& remix_lights::get_light_dir(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return lov && lov->_use_dir ? lov->dir : def.mDirection;
	}

	Vector remix_lights::get_light_color(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return lov && lov->_use_color ? lov->color : Vector(def.mColor);
	}

	float remix_lights::get_light_radius(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return 20.0f * (1.0f - exp(-(lov && lov->_use_radius ? lov->radius : def.mRadius) / 20.0f));
	}

	float remix_lights::get_light_intensity(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return lov && lov->_use_intensity ? lov->intensity : def.mIntensity;
	}

	float remix_lights::get_light_outer_cone_angle(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return lov &&  lov->_use_outer_cone_angle ? lov->outer_cone_angle
			 : lov && !lov->_use_outer_cone_angle && lov->light_type && def.mType != game::LT_SPOT ? lov->outer_cone_angle : def.mInnerConeAngle; // yes
	}

	float remix_lights::get_light_inner_cone_angle(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return lov &&  lov->_use_inner_cone_angle ? lov->inner_cone_angle
			 : lov && !lov->_use_inner_cone_angle && lov->light_type && def.mType != game::LT_SPOT ? lov->inner_cone_angle : def.mOuterConeAngle; // yes
	}

	float remix_lights::get_light_volumetric_scale(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return lov && lov->_use_volumetric_scale ? lov->volumetric_scale : def.mVolumeScale; // yes
	}

	// false = sphere ---- true = spotlight
	bool remix_lights::get_light_type(const game::CLightSource& def, const map_settings::light_override_s* lov) {
		return lov && lov->_use_light_type ? lov->light_type : def.mType == game::LT_SPOT; // yes
	}

	/**
	 * Spawns or updates a remixApi spherelight
	 * @param light			The light
	 * @param update		Is this light getting an update or completely new? 
	 * @param custom		Is this light custom and not created by the game? 
	 * @return				True if successfull
	 */
	bool remix_lights::spawn_or_update_remix_sphere_light(remix_light_def& light, bool update, bool custom)
	{
		const auto gs = comp_settings::get();
		auto msov = map_settings::get_map_settings().light_overrides;

		map_settings::light_override_s* lov = nullptr;
		if (const auto it = msov.find(light.m_hash); it != msov.end()) {
			lov = &it->second;
		}

		if (light.m_handle) {
			destroy_light(light);
		}

		light.m_updateframe = m_updateframe;

		const auto& def = light.m_def;
		const auto is_spotlight = get_light_type(def, lov);

		light.m_ext.sType = REMIXAPI_STRUCT_TYPE_LIGHT_INFO_SPHERE_EXT;
		light.m_ext.pNext = nullptr;
		light.m_ext.position = get_light_position(def, lov).ToRemixFloat3D();

		// scale down lights with larger radii (eg. own vehicle headlight (75 rad))
		light.m_ext.radius = custom ? def.mRadius : get_light_radius(def, lov) * gs->translate_game_light_radius_scalar.get_as<float>() * 0.01f;
		light.m_ext.shaping_hasvalue = is_spotlight;
		light.m_ext.shaping_value = {};
		light.m_ext.shaping_value.direction = get_light_dir(def, lov).ToRemixFloat3D();

		// "outer" param → actual inner cone (smaller)
		const float outerConeDegrees = RAD2DEG(get_light_outer_cone_angle(def, lov)); // "inner" param → outer cone (larger)
		const float coneSoftness = std::cos(get_light_inner_cone_angle(def, lov) * 0.5f) - std::cos(get_light_outer_cone_angle(def, lov) * 0.5f);

		light.m_ext.shaping_value.coneAngleDegrees = outerConeDegrees + gs->translate_game_light_angle_offset.get_as<float>();
		light.m_ext.shaping_value.coneSoftness = coneSoftness + gs->translate_game_light_softness_offset.get_as<float>();
		light.m_ext.shaping_value.focusExponent = 0.0f;

		light.m_ext.volumetricRadianceScale = 
			   get_light_volumetric_scale(def, lov)
			*  (is_spotlight ?
				  gs->translate_game_light_spotlight_volumetric_radiance_scale.get_as<float>() 
				: gs->translate_game_light_spherelight_volumetric_radiance_scale.get_as<float>());

		light.m_info.sType = REMIXAPI_STRUCT_TYPE_LIGHT_INFO;
		light.m_info.pNext = &light.m_ext;

		if (!update) {
			light.m_info.hash = light.m_hash;
		}
		
		if (custom) {
			light.m_info.radiance = (def.mIntensity * Vector(def.mColor)).ToRemixFloat3D();
		}
		else
		{
			light.m_info.radiance = (
				get_light_intensity(def, lov)
				* get_light_color(def, lov)
				* gs->translate_game_light_intensity_scalar.get_as<float>()).ToRemixFloat3D();
		}

		const auto& api = shared::common::remix_api::get();
		return api.m_bridge.CreateLight(&light.m_info, &light.m_handle) == REMIXAPI_ERROR_CODE_SUCCESS;
	}


	/**
	 * Adds and immediately spawns a single light
	 * @param def	The game light definition
	 */
	void remix_lights::add_light(const game::CLightSource& def, const uint64_t& hash, bool is_filler, const bool add_but_do_not_draw)
	{
		if (def.mType == game::LT_POINT || def.mType == game::LT_SPOT)
		{
			auto& l = m_active_lights[hash];
			l.m_def = def;
			l.m_hash = hash;
			l.m_light_num = m_active_light_spawn_tracker++;
			l.m_is_filler = is_filler;

			// add light with 0 intensity (eg. for debug vizualizations)
			if (add_but_do_not_draw)
			{
				l.m_def.mIntensity = 0.0f;
				l.m_is_ignored = true;
			}

			get()->spawn_or_update_remix_sphere_light(l);
		}
	}

	/**
	 * Destroys a remixApi light
	 * @param l		The light to destroy
	 */
	void remix_lights::destroy_light(remix_light_def& l)
	{
		if (l.m_handle)
		{
			shared::common::remix_api::get().m_bridge.DestroyLight(l.m_handle);
			l.m_handle = nullptr;
		}
	}

	/**
	 * Destroys all lights in 'm_map_lights' (remixApi lights)
	 */
	void remix_lights::destroy_all_lights()
	{
		for (auto& l : m_active_lights) {
			destroy_light(l.second);
		}
	}

	/**
	 * Destroys and clears all active remixApi lights
	 */
	void remix_lights::destroy_and_clear_all_active_lights()
	{
		destroy_all_lights();
		m_active_lights.clear();
	}

	/**
	 * Draw all active remixApi lights
	 */

	void remix_lights::draw_all_active_lights()
	{
		for (auto& l : m_active_lights)
		{
			if (l.second.m_handle) {
				shared::common::remix_api::get().m_bridge.DrawLightInstance(l.second.m_handle);
			}
		}
	}

	// #
	// #

	void remix_lights::on_client_frame()
	{
		const auto rml = remix_lights::get();
		const auto gl = game_lights::get();

		// check if paused
		rml->m_is_paused = *game::CMenuManager__m_MenuActive;

		if (!rml->m_is_paused)
		{
			rml->m_updateframe++;
			gl->iterate_all_game_lights();
		}

		rml->draw_all_active_lights();
		gl->draw_debug();
	}

	// not in use
	void remix_lights::reset()
	{
		// reset spawn tracker
		m_active_light_spawn_tracker = 0u;
	}

	void on_render_light_list_hk()
	{
		if (shared::common::remix_api::is_initialized()) {
			remix_lights::on_client_frame();
		}
	}

	void __declspec(naked) on_render_light_list_stub()
	{
		__asm
		{
			mov     ebp, esp;
			and		esp, 0xFFFFFFF0;

			pushad;
			call	on_render_light_list_hk;
			popad;

			jmp		game::retn_addr__on_render_light_list_stub;
		}
	}

	remix_lights::remix_lights()
	{
		p_this = this;

		shared::utils::hook(game::retn_addr__on_render_light_list_stub - 5u, on_render_light_list_stub, HOOK_JUMP).install()->quick(); // 0xAC1031

		// -----
		m_initialized = true;
		shared::common::log("RemixLights", "Module initialized.", shared::common::LOG_TYPE::LOG_TYPE_DEFAULT, false);
	}
}
