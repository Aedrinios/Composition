#include <Helpers/ImageProcessingHelper.h>
#include "UserInterface.h"

//
// Created by gacon on 30/01/2021.
//
void UserInterface::start(){
    cout << "Composition d'images! Trop bien! " << endl;

    //Set up images
    cout << "Veuillez entrer le nom du dossier contenant toutes les images à traiter" << endl;
    getline (cin, _name_folder_in);
    while(!FileHelper::exist(_name_folder_in) && _name_folder_in!=""){
        cout << "Ce dossier n'existe pas..." << endl;
        cout << "Veuillez entrer le nom du dossier contenant toutes les images à traiter ET QUI EXISTE CETTE FOIS CI" << endl;
        getline (cin, _name_folder_in);
    }
    if(_name_folder_in==""){
        _name_folder_in="resources/images";
    }
    string name_file;
    ostringstream stream;
    for (const auto & entry : filesystem::directory_iterator(_name_folder_in)){
        stream << entry.path();
        name_file = stream.str();
        name_file.erase(name_file.end()-1);
        name_file.erase(name_file.begin());
        Image img(name_file);
        _images.push_back(img);
        stream.str("");
        stream.clear();
    }

    settings();

    //Export image
    cout << "Traitement d'image terminée! Dans quel dossier voulez-vous exporter le résultat?" << endl;
    getline (cin, _name_folder_out);
    if(_name_folder_out==""){
        _name_folder_out="out";
    }
    if (!FileHelper::exist("../"+_name_folder_out)){
        FileHelper::createDirectory("../"+_name_folder_out);
    }
    /*for (int i=0; i < _images.size(); i++) {
        _images[i].write("../"+_name_folder_out+"/oui"+to_string(i)+".jpg");
    }*/
    Image result = ImageProcessingHelper::median_images(_images);
    result.write("../"+_name_folder_out+"result.jpg");
}

void UserInterface::settings() {
    int index=0;
    string tmp;
    while(index!=1){
        cout << "Que souhaitez-vous faire?" << endl;
        cout << "1 - Lancer le programme" << endl;
        cout << "2 - Modifier la tolérance (Actuellement : " + to_string(_tolerance) + ")" << endl;
        cout << "3 - Modifier la taille minimum d'un composant connexe (Actuellement : " + to_string(_min_size_connexe) + ")" << endl;
        cout << "4 - Activer/Désactiver le Fading" << endl;
        getline (cin, tmp);
        index = stoi(tmp);
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
            default:
                break;
        }
    }
}

void UserInterface::enter_tolerance(){
    string tmp;
    cout << "Tolerance pour le traitement du background (%)" << endl;
    getline (cin, tmp);
    _tolerance = stoi(tmp);
}

void UserInterface::enter_size_connexe(){
    string tmp;
    cout << "Taille minimum d'une composante connexe (nombre de pixel)" << endl;
    getline (cin, tmp);
    _min_size_connexe = stoi(tmp);
}

void UserInterface::enter_fading(){
    string tmp;
    if(_fading_state==0){
        cout << "Activer le fading?   y/n " << endl;
        getline (cin, tmp);
        if(tmp=="y" || tmp=="Y" || tmp=="yes"){
            cout << "Effet croissant ou décroissant?" << endl;
            cout << "1 - Croissant" << endl;
            cout << "2 - Décroissant" << endl;
            getline (cin, tmp);
            if(stoi(tmp) == 1){
                _fading_state=1;
            }
            else if (stoi(tmp) == 2){
                _fading_state=2;
            }
        }
    }
    else{
        cout << "Désactiver le fading?   y/n " << endl;
        getline (cin, tmp);
        if(tmp=="y" || tmp=="Y" || tmp=="yes"){
            _fading_state=0;
        }
    }
}

vector<Image> UserInterface::getImages(){
    return _images;
}