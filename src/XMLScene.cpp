/*
 * ao juntar com o criador da estrutura de dados adicionar as verificações de se
 * a textura está definida e no final de se todos os nós foram definidos
 *
 * e se o ficheiro da textura existe
 *
 * e se noderef já tinha sido percorrido ou não
 *
 *
 * conisses: usar excecões em vez de return _bool_ e usar queryBool
 *
 * confirmar com o Wilson o como ele pôs as primitivas no grafo : testar Node has already been processed
 */

#include "XMLScene.h"
#include <iostream>
#include <algorithm>

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

	if (!parseGraph())
		exit(-1);

	printf("\n\n");
}

XMLScene::~XMLScene() {
	delete (doc);
}

TiXmlElement *XMLScene::findChildByAttribute(TiXmlElement *parent,
        const char * attr, const char *val) {
	TiXmlElement *child = parent->FirstChildElement();
	bool found = false;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr), val) == 0)
			found = true;
		else
			child = child->NextSiblingElement();
	if (!found)
		return NULL;
	else
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
			        persp_cam_angle, persp_cam_pos_x, persp_cam_pos_y,
			        persp_cam_pos_z, persp_cam_targ_x, persp_cam_targ_y,
			        persp_cam_targ_z);
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

	if (lights_counter > 8 || lights_counter < 1) {
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

			printf("kdkdk");
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

			if (strcpy(app_text_ref, app->Attribute("textureref")) != NULL) {
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
			} else {
				strcpy(app_text_ref, "none");
				app_text_len_s = 0.0;
				app_text_len_t = 0.0;
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

	printf("Processing graph...\n\n");

	char root_id[MAX_STRING_LEN];

	if (strcpy(root_id, graphElement->Attribute("rootid")) == NULL) {
		printf("Error reading \"rootid\"\n");
		return false;
	}

	TiXmlElement *curr_node = NULL;
	if ((curr_node = findChildByAttribute(graphElement, "id", root_id)) == NULL) {
		printf("The root node is not declared in the file!\n");
		return false;
	}

	vector<string> nodes_processed;

	if (!parseNode(curr_node, nodes_processed)) {
		return false;
	}
	return true;
}

bool XMLScene::parseNode(TiXmlElement *curr_node,
        vector<string> nodes_processed) {
	char node_id[MAX_STRING_LEN];

	if (strcpy(node_id, curr_node->Attribute("id")) == NULL) {
		printf("Error reading \"id\" attribute!\n");
		return false;
	}

	printf("id: %s\n", node_id);

	nodes_processed.push_back(node_id);

	printf("Processing transformations...\n");

	TiXmlElement *transf_block = NULL;
	if ((transf_block = curr_node->FirstChildElement("transforms")) == NULL) {
		printf("Could not find \"transforms\" block on %s node!\n", node_id);
		return false;
	}

	TiXmlElement *transf = NULL;
	while ((transf = (TiXmlElement*) transf_block->IterateChildren(transf))) {
		char t_type[MAX_STRING_LEN];
		if (strcpy(t_type, transf->Value()) == NULL) {
			printf("Invalid transformation on node %s\n", node_id);
			return false;
		}
		if (strcmp(t_type, "translate") == 0) {
			char tmp_str[MAX_STRING_LEN];
			double t_x = 0, t_y = 0, t_z = 0;

			if (strcpy(tmp_str, transf->Attribute("to")) == NULL) {
				printf("Error on translate transformation on node %s!\n",
				        node_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf", &t_x, &t_y, &t_z) != 3) {
				printf("Error parsing translate transformation on node %s!\n",
				        node_id);
				return false;
			}

			printf("Translate\nto: (%f %f %f)\n", t_x, t_y, t_z);

		} else if (strcmp(t_type, "rotate") == 0) {
			char tmp_str[2];
			char r_axis = '\0';
			double r_angle;
			if (strcpy(tmp_str, transf->Attribute("axis")) == NULL) {
				printf("Error on rotate transformation on node %s!\n", node_id);
				return false;
			}
			r_axis = tmp_str[0];

			if (transf->QueryDoubleAttribute("angle", &r_angle)) {
				printf("Error parsing rotate transformation on node %s!\n",
				        node_id);
				return false;
			}
			printf("Rotate\naxis: %c\nangle: %f\n", r_axis, r_angle);

		} else if (strcmp(t_type, "scale") == 0) {
			char tmp_str[MAX_STRING_LEN];
			double f_x = 0, f_y = 0, f_z = 0;

			if (strcpy(tmp_str, transf->Attribute("factor")) == NULL) {
				printf("Error on scale transformation on node %s!\n", node_id);
				return false;
			}

			if (sscanf(tmp_str, "%lf %lf %lf", &f_x, &f_y, &f_z) != 3) {
				printf("Error parsing scale transformation on node %s!\n",
				        node_id);
				return false;
			}

			printf("Scale\nfactor: (%f %f %f)\n", f_x, f_y, f_z);

		} else {
			printf("Invalid transformation on node %s\n", node_id);
			return false;
		}
	}

	TiXmlElement *appearance = NULL;
	if ((appearance = curr_node->FirstChildElement("appearanceref"))) {
		char app_id[MAX_STRING_LEN];
		if (strcpy(app_id, appearance->Attribute("id")) == NULL) {
			printf("Error on \"appearanceref\" block on node %s!\n", node_id);
			return false;
		}
		printf("Appearance\nid: %s\n", app_id);
	} else {
		printf("No \"appearanceref\" block found on node %s!\n", node_id);
	}

	printf("Processing children...\n");

	TiXmlElement *children = NULL;

	if ((children = curr_node->FirstChildElement("children")) == NULL) {
		printf("Block \"children\" not found!\n");
		return false;
	}

	TiXmlElement *child = NULL;
	while ((child = (TiXmlElement *) children->IterateChildren(child))) {
		char child_type[MAX_STRING_LEN];
		strcpy(child_type, child->Value());

		if (strcmp(child_type, "rectangle") == 0) {
			char tmp_str[MAX_STRING_LEN];
			double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			if (strcpy(tmp_str, child->Attribute("xy1")) == NULL) {
				printf("Error reading \"xy1\" attribute!\n");
				return false;
			}
			if (sscanf(tmp_str, "%lf %lf", &x1, &y1) != 2) {
				printf("Error parsing \"xy1\" attribute!\n");
				return false;
			}

			if (strcpy(tmp_str, child->Attribute("xy2")) == NULL) {
				printf("Error reading \"xy2\" attribute!\n");
				return false;
			}
			if (sscanf(tmp_str, "%lf %lf", &x2, &y2) != 2) {
				printf("Error parsing \"xy2\" attribute!\n");
				return false;
			}

			printf("Rectangle\nxy1: (%f,%f)\nxy2: (%f,%f)\n", x1, y1, x2, y2);

		} else if (strcmp(child_type, "triangle") == 0) {
			char tmp_str[MAX_STRING_LEN];
			double x1 = 0, x2 = 0, x3 = 0, y1 = 0, y2 = 0, y3 = 0, z1 = 0, z2 =
			        0, z3 = 0;
			if (strcpy(tmp_str, child->Attribute("xyz1")) == NULL) {
				printf("Error reading \"xyz1\" attribute!\n");
				return false;
			}
			if (sscanf(tmp_str, "%lf %lf %lf", &x1, &y1, &z1) != 3) {
				printf("Error parsing \"xyz1\" attribute!\n");
				return false;
			}

			if (strcpy(tmp_str, child->Attribute("xyz2")) == NULL) {
				printf("Error reading \"xyz2\" attribute!\n");
				return false;
			}
			if (sscanf(tmp_str, "%lf %lf %lf", &x2, &y2, &z2) != 3) {
				printf("Error parsing \"xyz2\" attribute!\n");
				return false;
			}

			if (strcpy(tmp_str, child->Attribute("xyz3")) == NULL) {
				printf("Error reading \"xyz3\" attribute!\n");
				return false;
			}
			if (sscanf(tmp_str, "%lf %lf %lf", &x3, &y3, &z3) != 3) {
				printf("Error parsing \"xyz3\" attribute!\n");
				return false;
			}

			printf(
			        "Triangle\nxyz1: (%f,%f,%f)\nxyz2: (%f,%f,%f)\nxyz3: (%f,%f,%f)\n",
			        x1, y1, z1, x2, y2, z2, x3, y3, z3);

		} else if (strcmp(child_type, "cylinder") == 0) {
			double cyl_base = 0, cyl_top = 0, cyl_height = 0;
			unsigned int cyl_slices = 0, cyl_stacks = 0;

			if (child->QueryDoubleAttribute("base", &cyl_base)
			        != TIXML_SUCCESS) {
				printf("Error parsing base attribute!\n");
				return false;
			}

			if (child->QueryDoubleAttribute("top", &cyl_top) != TIXML_SUCCESS) {
				printf("Error parsing slices attribute!\n");
				return false;
			}

			if (child->QueryDoubleAttribute("height", &cyl_height)
			        != TIXML_SUCCESS) {
				printf("Error parsing slices attribute!\n");
				return false;
			}

			if (child->QueryUnsignedAttribute("slices", &cyl_slices)
			        != TIXML_SUCCESS) {
				printf("Error parsing slices attribute!\n");
				return false;
			}

			if (child->QueryUnsignedAttribute("stacks", &cyl_stacks)
			        != TIXML_SUCCESS) {
				printf("Error parsing stacks attribute!\n");
				return false;
			}

			printf(
			        "Cylinder\nbase: %f\ntop: %f\nheight: %f\nslices: %d\nstacks: %d\n",
			        cyl_base, cyl_top, cyl_height, cyl_slices, cyl_stacks);

		} else if (strcmp(child_type, "sphere") == 0) {
			double sph_rad = 0;
			unsigned int sph_slices = 0, sph_stacks = 0;

			if (child->QueryDoubleAttribute("radius", &sph_rad)
			        != TIXML_SUCCESS) {
				printf("Error parsing radius attribute!\n");
			}

			if (child->QueryUnsignedAttribute("slices", &sph_slices)
			        != TIXML_SUCCESS) {
				printf("Error parsing slices attribute!\n");
			}

			if (child->QueryUnsignedAttribute("stacks", &sph_stacks)
			        != TIXML_SUCCESS) {
				printf("Error parsing stacks attribute!\n");
			}

			printf("Sphere\nradius: %f\nslices: %d\nstacks: %d\n", sph_rad,
			        sph_slices, sph_stacks);

		} else if (strcmp(child_type, "torus") == 0) {
			double tor_inner = 0, tor_out = 0;
			unsigned int tor_slices = 0, tor_loops = 0;

			if (child->QueryDoubleAttribute("inner", &tor_inner)
			        != TIXML_SUCCESS) {
				printf("Error parsing inner attribute!\n");
			}

			if (child->QueryDoubleAttribute("outer", &tor_out)
			        != TIXML_SUCCESS) {
				printf("Error parsing outer attribute!\n");
			}

			if (child->QueryUnsignedAttribute("slices", &tor_slices)
			        != TIXML_SUCCESS) {
				printf("Error parsing slices attribute!\n");
			}

			if (child->QueryUnsignedAttribute("loops", &tor_loops)
			        != TIXML_SUCCESS) {
				printf("Error parsing loops attribute!\n");
			}

			printf("Torus\ninner: %f\nouter: %f\nslices: %d\nloops: %d\n",
			        tor_inner, tor_out, tor_slices, tor_loops);

		} else if (strcmp(child_type, "noderef") == 0) {
			char next_node_id[MAX_STRING_LEN];
			if (strcpy(next_node_id, child->Attribute("id")) == NULL) {
				printf("Error reading noderef's id!\n");
				return false;
			}
			if (find(nodes_processed.begin(), nodes_processed.end(),
			        next_node_id) != nodes_processed.end()) {
				printf("Node has already been processed.\n");
				continue;
			} else {
				TiXmlElement *next_node = NULL;
				if ((next_node = findChildByAttribute(graphElement, "id",
				        next_node_id))) {
					printf("\n\n");
					parseNode(next_node, nodes_processed);
				} else {
					printf("Node %s does not exist!\n", next_node_id);
					return false;
				}
			}
		} else {
			printf("Invalid block inside children of node %s\n", node_id);
		}
	}
	printf("Finished processing %s node children.\n\n", node_id);
	return true;
}
