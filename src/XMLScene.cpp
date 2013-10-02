/*
 * ao juntar com o criador da estrutura de dados adicionar as verificações de se
 * a textura está definida e no final de se todos os nós foram definidos
 *
 * e se o ficheiro da textura existe
 */

#include "XMLScene.h"

#define MAX_STRING_LEN 256

XMLScene::XMLScene(char *filename) {

	// Read XML from file

	doc = new TiXmlDocument(filename);
	bool loadOkay = doc->LoadFile();

	if (!loadOkay) {
		printf("Could not load file '%s'. Error='%s'.\n", filename,
		        doc->ErrorDesc());
		exit(-1);
	}

	TiXmlElement* yafElement = doc->FirstChildElement("yaf");

	if (yafElement == NULL) {
		printf("Main yaf block element not found!\n");
		exit(-1);
	}

	if ((globalsElement = yafElement->FirstChildElement("globals")) == NULL) {
		printf("Globals block not found!\n");
		exit(-1);
	}
	if ((camerasElement = yafElement->FirstChildElement("cameras")) == NULL) {
		printf("Cameras block not found!\n");
		exit(-1);
	}
	if ((lightingElement = yafElement->FirstChildElement("lighting")) == NULL) {
		printf("Lighting block not found!\n");
		exit(-1);
	}
	if ((texturesElement = yafElement->FirstChildElement("textures")) == NULL) {
		printf("Textures block not found!\n");
		exit(-1);
	}
	if ((appearencesElement = yafElement->FirstChildElement("appearances"))
	        == NULL) {
		printf("Appearences block not found!\n");
		exit(-1);
	}
	if ((graphElement = yafElement->FirstChildElement("graph")) == NULL) {
		printf("Graph block not found!\n");
		exit(-1);
	}

	if (!parseGlobals())
		exit(-1);

	printf("\n\n");

	if (!parseCameras())
		exit(-1);

	printf("\n\n");

	if (!parseLighting())
		exit(-1);

	printf("\n\n");

	if (!parseTextures())
		exit(-1);

	printf("\n\n");

	if (!parseAppearences())
		exit(-1);

	printf("\n\n");

}

XMLScene::~XMLScene() {
	delete (doc);
}

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,
        const char * attr, const char *val)
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
        {
	TiXmlElement *child = parent->FirstChildElement();
	int found = 0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr), val) == 0)
			found = 1;
		else
			child = child->NextSiblingElement();

	return child;
}

bool XMLScene::parseGlobals() {
	printf("Processing globals...\n\n");
	char background_str[9];
	double back_r = 0, back_g = 0, back_b = 0, back_a = 0;

	if ((strcpy(background_str, globalsElement->Attribute("background")))
	        == NULL) {
		printf("Error parsing background!\n");
		return false;
	}

	if (sscanf(background_str, "%lf %lf %lf %lf", &back_r, &back_g, &back_b,
	        &back_a) != 4) {
		printf("Invalid arguments of background!\n");
		return false;
	}

// Success parsing background
	printf("background attributes: %f %f %f %f", back_r, back_g, back_b,
	        back_a);
	return true;
}

bool XMLScene::parseCameras() {
	bool valid_nr_cameras = false;
	printf("Processing cameras...\n\n");
	char init_camera[MAX_STRING_LEN];
	if ((strcpy(init_camera, camerasElement->Attribute("initial"))) == NULL) {
		printf("Error parsing background!\n");
		exit(-1);
	}

	printf("Initial camera: %s\n", init_camera);

	TiXmlElement * persp_cam = NULL;
	TiXmlElement * ortho_cam = NULL;

	if ((persp_cam = camerasElement->FirstChildElement("perspective")) != NULL) {
		valid_nr_cameras = true;
		char persp_cam_id[MAX_STRING_LEN];
		char persp_cam_pos[MAX_STRING_LEN];
		char persp_cam_targ[MAX_STRING_LEN];
		double persp_cam_near = 0, persp_cam_far = 0, persp_cam_angle = 0,
		        persp_cam_pos_x = 0, persp_cam_pos_y = 0, persp_cam_pos_z = 0,
		        persp_cam_targ_x = 0, persp_cam_targ_y = 0,
		        persp_cam_targ_z = 0;

		do {
			if ((strcpy(persp_cam_id, persp_cam->Attribute("id"))) == NULL) {
				printf("Error parsing perspective camera id!\n");
				return false;
			}

			if (persp_cam->Attribute("near", &persp_cam_near) == NULL) {
				printf("Error parsing \"%s\" camera near field!\n",
				        persp_cam_id);
				return false;
			}

			if (persp_cam->Attribute("far", &persp_cam_far) == NULL) {
				printf("Error parsing \"%s\" camera far field!\n",
				        persp_cam_id);
				return false;
			}

			if (persp_cam->Attribute("angle", &persp_cam_angle) == NULL) {
				printf("Error parsing \"%s\" camera angle field!\n",
				        persp_cam_id);
				return false;
			}

			if ((strcpy(persp_cam_pos, persp_cam->Attribute("pos"))) == NULL) {
				printf("Error parsing \"%s\" camera pos field!\n",
				        persp_cam_id);
				return false;
			}

			if (sscanf(persp_cam_pos, "%lf %lf %lf", &persp_cam_pos_x,
			        &persp_cam_pos_y, &persp_cam_pos_z) != 3) {
				printf("Invalid arguments of \"%s\" camera pos!\n",
				        persp_cam_id);
				return false;
			}

			if ((strcpy(persp_cam_targ, persp_cam->Attribute("target"))) == NULL) {
				printf("Error parsing \"%s\" camera target field!\n",
				        persp_cam_id);
				return false;
			}

			if (sscanf(persp_cam_targ, "%lf %lf %lf", &persp_cam_targ_x,
			        &persp_cam_targ_y, &persp_cam_targ_z) != 3) {
				printf("Invalid arguments of \"%s\" camera target!\n",
				        persp_cam_id);
				return false;
			}
			printf(
			        "Perspective camera.\nid: %s\nnear: %f\nfar: %f\nangle: %f\npos: (%f,%f,%f)\ntarget: (%f,%f,%f)\n\n",
			        persp_cam_id, persp_cam_near, persp_cam_far,
			        persp_cam_pos_x, persp_cam_pos_y, persp_cam_pos_z,
			        persp_cam_targ_x, persp_cam_targ_y, persp_cam_targ_z);
		} while ((persp_cam = persp_cam->NextSiblingElement("perspective"))
		        != NULL);
	} else {
		printf("There are no perspective cameras.\n");
	}

	if ((ortho_cam = camerasElement->FirstChildElement("ortho")) != NULL) {
		valid_nr_cameras = true;
		char ortho_cam_id[MAX_STRING_LEN];
		double ortho_cam_near = 0, ortho_cam_far = 0, ortho_cam_left = 0,
		        ortho_cam_right = 0, ortho_cam_top = 0, ortho_cam_bottom = 0;
		do {

			if ((strcpy(ortho_cam_id, ortho_cam->Attribute("id"))) == NULL) {
				printf("Error parsing ortho camera id!\n");
				return false;
			}

			if (ortho_cam->Attribute("near", &ortho_cam_near) == NULL) {
				printf("Error parsing \"%s\" camera near field!\n",
				        ortho_cam_id);
				return false;
			}

			if (ortho_cam->Attribute("far", &ortho_cam_far) == NULL) {
				printf("Error parsing \"%s\" camera far field!\n",
				        ortho_cam_id);
				return false;
			}

			if (ortho_cam->Attribute("left", &ortho_cam_left) == NULL) {
				printf("Error parsing \"%s\" camera left field!\n",
				        ortho_cam_id);
				return false;
			}

			if (ortho_cam->Attribute("right", &ortho_cam_right) == NULL) {
				printf("Error parsing \"%s\" camera right field!\n",
				        ortho_cam_id);
				return false;
			}

			if (ortho_cam->Attribute("top", &ortho_cam_top) == NULL) {
				printf("Error parsing \"%s\" camera top field!\n",
				        ortho_cam_id);
				return false;
			}

			if (ortho_cam->Attribute("bottom", &ortho_cam_bottom) == NULL) {
				printf("Error parsing \"%s\" camera bottom field!\n",
				        ortho_cam_id);
				return false;
			}
			printf(
			        "Ortho camera.\nid: %s\nnear: %f\nfar: %f\nleft: %f\nright: %f\ntop: %f\nbottom: %f\n\n",
			        ortho_cam_id, ortho_cam_near, ortho_cam_far, ortho_cam_left,
			        ortho_cam_right, ortho_cam_top, ortho_cam_bottom);
		} while ((ortho_cam = ortho_cam->NextSiblingElement("ortho")) != NULL);

	} else {
		printf("There are no ortho cameras.\n");
	}
	if (!valid_nr_cameras) {
		printf("There must be at least one camera defined!\n");
		return false;
	}
	return true;
}

bool XMLScene::parseLighting() {
	bool valid_nr_lights = false;
	unsigned int lights_counter = 0;
	printf("Processing lights...\n\n");
	char tmp_str[MAX_STRING_LEN];
	bool is_doublesided = false, is_local = true, is_enabled = true;
	double light_amb_r = 0, light_amb_g = 0, light_amb_b = 0, light_amb_a = 0;

	if (strcpy(tmp_str, lightingElement->Attribute("doublesided")) == NULL) {
		printf("Invalid argument of doublesided!\n");
		return false;
	}
	if (strcmp(tmp_str, "true") == 0) {
		is_doublesided = true;
	} else if (strcmp(tmp_str, "false") == 0) {
		is_doublesided = false;
	} else {
		printf("Invalid argument of doublesided!\n");
		return false;
	}

	if (strcpy(tmp_str, lightingElement->Attribute("local")) == NULL) {
		printf("Invalid argument of local!\n");
		return false;
	}
	if (strcmp(tmp_str, "true") == 0) {
		is_local = true;
	} else if (strcmp(tmp_str, "false") == 0) {
		is_local = false;
	} else {
		printf("Invalid argument of local!\n");
		return false;
	}

	if (strcpy(tmp_str, lightingElement->Attribute("enabled")) == NULL) {
		printf("Invalid argument of enabled!\n");
		return false;
	}
	if (strcmp(tmp_str, "true") == 0) {
		is_enabled = true;
	} else if (strcmp(tmp_str, "false") == 0) {
		is_enabled = false;
	} else {
		printf("Invalid argument of enabled!\n");
		return false;
	}

	if (strcpy(tmp_str, lightingElement->Attribute("ambient")) == NULL) {
		printf("Invalid argument of ambient!\n");
		return false;
	}

	if (sscanf(tmp_str, "%lf %lf %lf %lf", &light_amb_r, &light_amb_g,
	        &light_amb_b, &light_amb_a) != 4) {
		printf("Invalid argument of ambient!\n");
		return false;
	}

	printf(
	        "Global lightign attributes.\ndoublesided: %s\nlocal: %s\nenabled: %s\nambient: (%f,%f,%f,%f)\n\n",
	        is_doublesided ? "true" : "false", is_local ? "true" : "false",
	        is_enabled ? "true" : "false", light_amb_r, light_amb_g,
	        light_amb_b, light_amb_a);

	TiXmlElement *omni = NULL, *spot = NULL;

	if ((omni = lightingElement->FirstChildElement("omni")) != NULL) {
		valid_nr_lights = true;
		do {
			lights_counter++;
			char omni_id[MAX_STRING_LEN], tmp_str[MAX_STRING_LEN];
			bool omni_enabled = false;
			double omni_location_x = 0, omni_location_y = 0,
			        omni_location_z = 0, omni_amb_r = 0, omni_amb_g = 0,
			        omni_amb_b = 0, omni_amb_a = 0, omni_dif_r = 0, omni_dif_g =
			                0, omni_dif_b = 0, omni_dif_a = 0, omni_spec_r = 0,
			        omni_spec_g = 0, omni_spec_b = 0, omni_spec_a = 0;
			if (strcpy(omni_id, omni->Attribute("id")) == NULL) {
				printf("Invalid id argument!\n");
				return false;
			}

			if (strcpy(tmp_str, omni->Attribute("enabled")) == NULL) {
				printf("Error on atribute \"enabled\" of %s light!\n", omni_id);
				return false;
			}

			if (strcmp(tmp_str, "true") == 0) {
				omni_enabled = true;
			} else if (strcmp(tmp_str, "false") == 0) {
				omni_enabled = false;
			} else {
				printf("Invalid argument of local!\n");
				return false;
			}

			if (strcpy(tmp_str, omni->Attribute("location")) == NULL) {
				printf("No attribute \"location\" of %s light!\n", omni_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf", &omni_location_x,
			        &omni_location_y, &omni_location_z) != 3) {
				printf("Invalid location argument of %s light!\n", omni_id);
				return false;
			}

			if (strcpy(tmp_str, omni->Attribute("ambient")) == NULL) {
				printf("No attribute \"ambient\" of %s light!\n", omni_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &omni_amb_r, &omni_amb_g,
			        &omni_amb_b, &omni_amb_a) != 4) {
				printf("Invalid ambient argument of %s light!\n", omni_id);
				return false;
			}

			if (strcpy(tmp_str, omni->Attribute("diffuse")) == NULL) {
				printf("No attribute \"diffuse\" of %s light!\n", omni_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &omni_dif_r, &omni_dif_g,
			        &omni_dif_b, &omni_dif_a) != 4) {
				printf("Invalid diffuse argument of %s light!\n", omni_id);
				return false;
			}

			if (strcpy(tmp_str, omni->Attribute("specular")) == NULL) {
				printf("No attribute \"specular\" of %s light!\n", omni_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &omni_spec_r, &omni_spec_g,
			        &omni_spec_b, &omni_spec_a) != 4) {
				printf("Invalid specular argument of %s light!\n", omni_id);
				return false;
			}
			printf(
			        "Omni light.\nid: %s\nenabled: %s\nlocation: (%f,%f,%f)\nambient: (%f,%f,%f,%f)\ndiffuse: (%f,%f,%f,%f)\nspecular: (%f,%f,%f,%f)\n\n",
			        omni_id, omni_enabled ? "true" : "false", omni_location_x,
			        omni_location_y, omni_location_z, omni_amb_r, omni_amb_g,
			        omni_amb_b, omni_amb_a, omni_dif_r, omni_dif_g, omni_dif_b,
			        omni_dif_a, omni_spec_r, omni_spec_g, omni_spec_b,
			        omni_spec_a);
		} while ((omni = omni->NextSiblingElement("omni")) != NULL);
	} else {
		printf("There are no omni lights.\n");
	}

	if ((spot = lightingElement->FirstChildElement("spot")) != NULL) {
		valid_nr_lights = true;

		do {
			lights_counter++;
			char spot_id[MAX_STRING_LEN], tmp_str[MAX_STRING_LEN];
			bool spot_enabled = false;
			double spot_location_x = 0, spot_location_y = 0,
			        spot_location_z = 0, spot_amb_r = 0, spot_amb_g = 0,
			        spot_amb_b = 0, spot_amb_a = 0, spot_dif_r = 0, spot_dif_g =
			                0, spot_dif_b = 0, spot_dif_a = 0, spot_spec_r = 0,
			        spot_spec_g = 0, spot_spec_b = 0, spot_spec_a = 0,
			        spot_angle = 0, spot_exp = 0, spot_dir_x = 0,
			        spot_dir_y = 0, spot_dir_z = 0;

			if (strcpy(spot_id, spot->Attribute("id")) == NULL) {
				printf("Invalid id argument!\n");
				return false;
			}

			if (strcpy(tmp_str, spot->Attribute("enabled")) == NULL) {
				printf("Error on atribute \"enabled\" of %s light!\n", spot_id);
				return false;
			}

			if (strcmp(tmp_str, "true") == 0) {
				spot_enabled = true;
			} else if (strcmp(tmp_str, "false") == 0) {
				spot_enabled = false;
			} else {
				printf("Invalid argument of local!\n");
				return false;
			}

			if (strcpy(tmp_str, spot->Attribute("location")) == NULL) {
				printf("No attribute \"location\" of %s light!\n", spot_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf", &spot_location_x,
			        &spot_location_y, &spot_location_z) != 3) {
				printf("Invalid location argument of %s light!\n", spot_id);
				return false;
			}

			if (strcpy(tmp_str, spot->Attribute("ambient")) == NULL) {
				printf("No attribute \"ambient\" of %s light!\n", spot_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &spot_amb_r, &spot_amb_g,
			        &spot_amb_b, &spot_amb_a) != 4) {
				printf("Invalid ambient argument of %s light!\n", spot_id);
				return false;
			}

			if (strcpy(tmp_str, spot->Attribute("diffuse")) == NULL) {
				printf("No attribute \"diffuse\" of %s light!\n", spot_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &spot_dif_r, &spot_dif_g,
			        &spot_dif_b, &spot_dif_a) != 4) {
				printf("Invalid diffuse argument of %s light!\n", spot_id);
				return false;
			}

			if (strcpy(tmp_str, spot->Attribute("specular")) == NULL) {
				printf("No attribute \"specular\" of %s light!\n", spot_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &spot_spec_r, &spot_spec_g,
			        &spot_spec_b, &spot_spec_a) != 4) {
				printf("Invalid specular argument of %s light!\n", spot_id);
				return false;
			}

			if (spot->Attribute("angle", &spot_angle) == NULL) {
				printf("Invalid angle atribute of %s light!\n", spot_id);
				return false;
			}

			if (spot->Attribute("exponent", &spot_exp) == NULL) {
				printf("Invalid exponent atribute of %s light!\n", spot_id);
				return false;
			}

			if (strcpy(tmp_str, spot->Attribute("direction")) == NULL) {
				printf("No attribute \"direction\" of %s light!\n", spot_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf", &spot_dir_x, &spot_dir_y,
			        &spot_dir_z) != 3) {
				printf("Invalid location argument of %s light!\n", spot_id);
				return false;
			}
			printf(
			        "Spot light.\nid: %s\nenabled: %s\nlocation: (%f,%f,%f)\nambient: (%f,%f,%f,%f)\ndiffuse: (%f,%f,%f,%f)\nspec: (%f,%f,%f,%f)\nangle: %f\nexponent: %f\ndirection: (%f,%f,%f)\n\n",
			        spot_id, spot_enabled ? "true" : "false", spot_location_x,
			        spot_location_y, spot_location_z, spot_amb_r, spot_amb_g,
			        spot_amb_b, spot_amb_a, spot_dif_r, spot_dif_g, spot_dif_b,
			        spot_dif_a, spot_spec_r, spot_spec_g, spot_spec_b,
			        spot_spec_a, spot_angle, spot_exp, spot_dir_x, spot_dir_y,
			        spot_dir_z);
		} while ((spot = spot->NextSiblingElement("spot")) != NULL);
	} else {
		printf("There are no omni lights.\n");
	}

	if (lights_counter > 8) {
		printf(
		        "There are more lights than the ones that can be used. Exiting...\n");
		return false;
	}
	return true;
}

bool XMLScene::parseTextures() {

	printf("Processing textures...\n\n");

	TiXmlElement *text = NULL;
	if ((text = texturesElement->FirstChildElement("texture")) != NULL) {
		char text_id[MAX_STRING_LEN], text_file[MAX_STRING_LEN];
		do {
			if (strcpy(text_id, text->Attribute("id")) == NULL) {
				printf("Error in \"id\" attribute!\n");
				return false;
			}

			if (strcpy(text_file, text->Attribute("file")) == NULL) {
				printf("Error in \"file\" attribute!\n");
				return false;
			}
			printf("id: %s\nfile: %s\n\n", text_id, text_file);
		} while ((text = text->NextSiblingElement("texture")) != NULL);
	} else {
		printf("There are no defined textures.\n");
	}
	return true;
}

bool XMLScene::parseAppearences() {

	printf("Processing appearences...\n\n");

	bool valid_nr_appear = false;
	char tmp_str[MAX_STRING_LEN], app_id[MAX_STRING_LEN],
	        app_text_ref[MAX_STRING_LEN];
	double app_emiss_r = 0, app_emiss_g = 0, app_emiss_b = 0, app_emiss_a = 0,
	        app_amb_r = 0, app_amb_g = 0, app_amb_b = 0, app_amb_a = 0,
	        app_dif_r = 0, app_dif_g = 0, app_dif_b = 0, app_dif_a = 0,
	        app_spec_r = 0, app_spec_g = 0, app_spec_b = 0, app_spec_a = 0,
	        app_shin = 0, app_text_len_s = 0, app_text_len_t = 0;
	TiXmlElement * app = NULL;
	if ((app = appearencesElement->FirstChildElement("appearance")) != NULL) {
		valid_nr_appear = true;
		do {
			if (strcpy(app_id, app->Attribute("id")) == NULL) {
				printf("Error in \"id\" attribute!\n");
				return false;
			}

			if (strcpy(tmp_str, app->Attribute("emissive")) == NULL) {
				printf("Error in \"emissive\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &app_emiss_r, &app_emiss_g,
			        &app_emiss_b, &app_emiss_a) != 4) {
				printf(
				        "Error parsing \"emissive\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (strcpy(tmp_str, app->Attribute("ambient")) == NULL) {
				printf("Error in \"ambient\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &app_amb_r, &app_amb_g,
			        &app_amb_b, &app_amb_a) != 4) {
				printf(
				        "Error parsing \"ambient\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (strcpy(tmp_str, app->Attribute("diffuse")) == NULL) {
				printf("Error in \"diffuse\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &app_dif_r, &app_dif_g,
			        &app_dif_b, &app_dif_a) != 4) {
				printf(
				        "Error parsing \"diffuse\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (strcpy(tmp_str, app->Attribute("specular")) == NULL) {
				printf("Error in \"specular\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf %lf", &app_spec_r, &app_spec_g,
			        &app_spec_b, &app_spec_a) != 4) {
				printf(
				        "Error parsing \"specular\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (app->Attribute("shininess", &app_shin) == NULL) {
				printf(
				        "Error parsing \"shininess\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (strcpy(app_text_ref, app->Attribute("textureref")) == NULL) {
				printf("Error in \"textureref\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (app->Attribute("texlength_s", &app_text_len_s) == NULL) {
				printf(
				        "Error parsing \"texlength_s\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			if (app->Attribute("texlength_t", &app_text_len_t) == NULL) {
				printf(
				        "Error parsing \"texlength_t\" attribute of %s appearence!\n",
				        app_id);
				return false;
			}

			printf(
			        "id: %s\nemissive: (%f,%f,%f,%f)\nambient: (%f,%f,%f,%f)\ndiffuse: (%f,%f,%f,%f)\nspecular: (%f,%f,%f,%f)\nshininess: %f\ntextureref: %s\ntexlength_s: %f\ntextlength_t: %f\n\n",
			        app_id, app_emiss_r, app_emiss_g, app_emiss_b, app_emiss_a,
			        app_amb_r, app_amb_g, app_amb_b, app_amb_a, app_dif_r,
			        app_dif_g, app_dif_b, app_dif_a, app_spec_r, app_spec_g,
			        app_spec_b, app_spec_a, app_shin, app_text_ref,
			        app_text_len_s, app_text_len_t);

		} while ((app = app->NextSiblingElement("appearance")) != NULL);
	}
	if (!valid_nr_appear) {
		printf(
		        "There are no defined appearences!\nPlease define at least one\n");
		return false;
	}
	return true;
}

bool XMLScene::parseGraph() {
	/*
	 // graph section
	 if (graphElement == NULL)
	 printf("Graph block not found!\n");
	 else {
	 char *prefix = "  -";
	 TiXmlElement *node = graphElement->FirstChildElement();

	 while (node) {
	 printf("Node id '%s' - Descendants:\n", node->Attribute("id"));
	 TiXmlElement *child = node->FirstChildElement();
	 while (child) {
	 if (strcmp(child->Value(), "Node") == 0) {
	 // access node data by searching for its id in the nodes section

	 TiXmlElement *noderef = findChildByAttribute(nodesElement,
	 "id", child->Attribute("id"));

	 if (noderef) {
	 // print id
	 printf("  - Node id: '%s'\n", child->Attribute("id"));

	 // prints some of the data
	 printf("    - Material id: '%s' \n",
	 noderef->FirstChildElement("material")->Attribute(
	 "id"));
	 printf("    - Texture id: '%s' \n",
	 noderef->FirstChildElement("texture")->Attribute(
	 "id"));

	 // repeat for other leaf details
	 } else
	 printf(
	 "  - Node id: '%s': NOT FOUND IN THE NODES SECTION\n",
	 child->Attribute("id"));

	 }
	 if (strcmp(child->Value(), "Leaf") == 0) {
	 // access leaf data by searching for its id in the leaves section
	 TiXmlElement *leaf = findChildByAttribute(leavesElement,
	 "id", child->Attribute("id"));

	 if (leaf) {
	 // it is a leaf and it is present in the leaves section
	 printf("  - Leaf id: '%s' ; type: '%s'\n",
	 child->Attribute("id"),
	 leaf->Attribute("type"));

	 // repeat for other leaf details
	 } else
	 printf(
	 "  - Leaf id: '%s' - NOT FOUND IN THE LEAVES SECTION\n",
	 child->Attribute("id"));
	 }

	 child = child->NextSiblingElement();
	 }
	 node = node->NextSiblingElement();
	 }
	 }
	 */
}

