#include <Helpers/ImageProcessingHelper.h>
#include <Tools/Debug.h>
#include "UserInterface.h"
#include "Helpers/StringHelpers.h"

//
// Created by gacon on 30/01/2021.
//
void UserInterface::start() {
	std::cout << "Composition d'images! Trop bien! " << std::endl; //Greetings

	setUp_images(); //Set up the Image vector

	settings(); //Change parameters before image processing

	image_processing(); //Image processing then export
}

void UserInterface::setUp_images() {
	//Set up images
	std::cout << "Veuillez entrer le nom du dossier contenant toutes les images à traiter (" << _name_folder_in << ")"
	          << std::endl;
	getline(std::cin, _name_folder_in);
	while (!FileHelper::exist(_name_folder_in) && !_name_folder_in.empty()) {
		std::cout << "Ce dossier n'existe pas..." << std::endl;
		std::cout
				<< "Veuillez entrer le nom du dossier contenant toutes les images à traiter ET QUI EXISTE CETTE FOIS CI"
				<< " (resources/images/game)"
				<< std::endl;
		getline(std::cin, _name_folder_in);
	}
	if (_name_folder_in.empty()) {
		_name_folder_in = "resources/images/game";
	}
	std::string name_file;
	std::ostringstream stream;
	int count = 0;
	for (const auto &entry : std::filesystem::directory_iterator(_name_folder_in)) {
		if (count < _step || _step == 0) {
			stream << entry.path();
			name_file = stream.str();
			name_file.erase(name_file.end() - 1);
			name_file.erase(name_file.begin());
			Image img(name_file);
			_images.push_back(img);
			stream.str("");
			stream.clear();
			count++;
		} else {
			count = 0;
		}
	}
}

void UserInterface::settings() {
	int index = 0;
	std::string tmp;
	while (index != 1) {
		std::cout << "Que souhaitez-vous faire? (1)" << std::endl;
		std::cout << "1 - Lancer le programme" << std::endl;
		std::cout << "2 - Modifier la tolérance (Actuellement : " + std::to_string(_tolerance) + ")" << std::endl;
		std::cout << "3 - Modifier la taille minimum d'un composant connexe (Actuellement : " +
		             std::to_string(_min_size_connexe) + ")" << std::endl;
		std::cout << "4 - Activer/Désactiver le Fading" << std::endl;
		std::cout << "5 - Activer/Désactiver la step" << std::endl;
		std::cout << "6 - Modifier le type de fusion d'image (" << mergeType << ")" << std::endl;


		getline(std::cin, tmp);
		if (tmp.empty()) {
			tmp = "1";
		}
		index = StringHelper::StringToInt(tmp);
		switch (index) {
			case 2 :
				enter_tolerance();
				break;
			case 3 :
				enter_size_connexe();
				break;
			case 4 :
				enter_fading();
				break;
			case 5 :
				enter_step();
				break;
			case 6 :
				enter_merge_diff();
				break;
			default:
				break;
		}
	}
}

void UserInterface::image_processing() {
    std::cout << "Dans quel dossier voulez-vous exporter le résultat?" << " (" << _name_folder_out << ")" << std::endl;
    getline(std::cin, _name_folder_out);
    if (_name_folder_out.empty()) {
        _name_folder_out = "out";
    }
    if (!FileHelper::exist(_name_folder_out)) {
        FileHelper::createDirectory(_name_folder_out);
    }
    std::cout << mergeType<< std::endl;

    FileHelper::clearDirectory("_name_folder_out");
    Debug::log("begin : median_images");
    Image median = ImageProcessingHelper::median_images(_images);
    if(_images[0].getChannel()==3)
        median.write("../"+_name_folder_out+"/median.jpg");
    else if(_images[0].getChannel()==4)
        median.write("../"+_name_folder_out+"/median.png");
    Debug::log("end : median_images");
    Debug::log("begin : add_subjects");
    ImageProcessingHelper::detect_subjects(_images, median, _tolerance, _min_size_connexe);
    Debug::log("end : add_subjects");
    if (mergeType == 1 || mergeType == 4) {
        Debug::log("begin : merge_diff_images");
        if(_images[0].getChannel()==3)
            ImageProcessingHelper::merge_diff_images(_images, median, _fading_state).write(_name_folder_out+"/full.jpg");
        else if(_images[0].getChannel()==4)
            ImageProcessingHelper::merge_diff_images(_images, median, _fading_state).write(_name_folder_out+"/full.png");
        Debug::log("end : merge_diff_images");
    }
    if (mergeType == 2 || mergeType == 4) {
        Debug::log("begin : merge_diff_images_overlap");
        ImageProcessingHelper::merge_diff_images_overlap(_images, median).write(_name_folder_out + "/full-overlap.jpg");
        Debug::log("end : merge_diff_images_overlap");
    }
    if (mergeType == 3 || mergeType == 4) {
        Debug::log("begin : merge_diff_images_distance");
        ImageProcessingHelper::merge_diff_images_distance(_images, median, _distance).write(_name_folder_out + "/full-distance.jpg");
        Debug::log("end : merge_diff_images_distance");
    }

}

void UserInterface::enter_tolerance() {
	std::string tmp;
	std::cout << "Tolerance pour le traitement du background (%)" << std::endl;
	getline(std::cin, tmp);
	_tolerance = StringHelper::StringToInt(tmp);
}

void UserInterface::enter_size_connexe() {
	std::string tmp;
	std::cout << "Taille minimum d'une composante connexe (nombre de pixel)" << std::endl;
	getline(std::cin, tmp);
	_min_size_connexe = StringHelper::StringToInt(tmp);
}

void UserInterface::enter_fading() {
	std::string tmp;
	if (_fading_state == 0) {
		std::cout << "Activer le fading?   y/n " << std::endl;
		getline(std::cin, tmp);
		if (tmp == "y" || tmp == "Y" || tmp == "yes") {
			/*std::cout << "Effet croissant ou décroissant?" << std::endl;
			std::cout << "1 - Croissant" << std::endl;
			std::cout << "2 - Décroissant" << std::endl;
			getline(std::cin, tmp);
			if (StringHelper::StringToInt(tmp) == 1) {
				_fading_state = 1;
			} else if (StringHelper::StringToInt(tmp) == 2) {
				_fading_state = 2;
			}*/
            _fading_state=1;
		}
	} else {
		std::cout << "Désactiver le fading?   y/n " << std::endl;
		getline(std::cin, tmp);
		if (tmp == "y" || tmp == "Y" || tmp == "yes") {
			_fading_state = 0;
		}
	}
}

void UserInterface::enter_step() {
	std::string tmp;
	std::cout << "Nombre de step" << std::endl;
	getline(std::cin, tmp);
	_step = StringHelper::StringToInt(tmp);
}

void UserInterface::enter_merge_diff() {
	bool nextStep = false;
	while (!nextStep) {
		std::cout << "Choisir le type de fusion d'image  (" << mergeType << ")" << std::endl;
		std::cout << "1 - Default" << std::endl;
		std::cout << "2 - Overlap" << std::endl;
		std::cout << "3 - Distance" << std::endl;
		std::cout << "4 - All (generate all type)" << std::endl;

		std::string tmp;
		getline(std::cin, tmp);
		mergeType = StringHelper::StringToInt(tmp);
		if (mergeType < 1 || mergeType > 4) {
			std::cout << tmp << " n'existe pas dans les choix" << std::endl;
			nextStep = false;
		} else {
			nextStep = true;
		}
	}
	if(mergeType == 3 || mergeType == 4){
	    enter_distance();
	}
}

void UserInterface::enter_distance(){
    std::string tmp;
    std::cout << "Distance entre les sujets" << std::endl;
    getline (std::cin, tmp);
    _distance = StringHelper::StringToInt(tmp);
}

std::vector<Image> UserInterface::getImages(){
    return _images;
}