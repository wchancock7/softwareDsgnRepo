#include "CppRestOpenAPIClient/ApiClient.h"
#include "CppRestOpenAPIClient/ApiConfiguration.h"
#include "CppRestOpenAPIClient/ApiException.h"
#include "CppRestOpenAPIClient/api/PetApi.h"
#include "CppRestOpenAPIClient/model/Pet.h"

#include <iostream>
#include <memory>
//"auto" is a smart pointer object that handles memory management.

using namespace org::openapitools::client::api;
using namespace org::openapitools::client::model;

int main() {
    auto configuration = std::make_shared<ApiConfiguration>();
    configuration->setBaseUrl("https://petstore.swagger.io/v2");
    auto apiClient = std::make_shared<ApiClient>(configuration);
    PetApi petApi(apiClient);
    int petID = 67890;

    //POST New Pet with ID: petID
    std::cout << "\nCreating a new pet..." << std::endl;

    auto newPet = std::make_shared<Pet>();
    newPet->setId(petID);
    newPet->setName("Basset Hound");
    newPet->setStatus(Pet::StatusEnum::AVAILABLE);

    petApi.addPet(newPet).get();

    std::cout << "Pet created successfully!" << std::endl;

    //Get Pet by ID
    std::cout << "\nLooking up pet #" << petID << "..." << std::endl;

    std::shared_ptr<Pet> pet = petApi.getPetById(petID).get();
    std::cout << "Found pet: " << pet->getName() << std::endl;
    std::cout << "Status: " << pet->fromStatusEnum(pet->getStatus()) << std::endl;

    //POST Update Pet Status
    std::cout << "\nUpdating pet status..." << std::endl;
    pet->setStatus(Pet::StatusEnum::SOLD);
    petApi.updatePet(pet).get();
    std::cout << "Pet status updated successfully!\n" << std::endl;

    return 0;
}