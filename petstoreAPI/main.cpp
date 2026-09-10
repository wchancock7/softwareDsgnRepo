// main.cpp
//
// A minimal, beginner-friendly example of using the generated
// Petstore C++ API client.
//
// It does two things:
//   1. Fetches an existing pet by ID (a GET request)
//   2. Creates a new pet (a POST request)
//
// Every network call returns a pplx::task<T>. Think of a "task" as a
// promise: "I don't have the answer yet, but call .get() and I'll wait
// until I do (or throw if something went wrong)."

#include "CppRestOpenAPIClient/ApiClient.h"
#include "CppRestOpenAPIClient/ApiConfiguration.h"
#include "CppRestOpenAPIClient/ApiException.h"
#include "CppRestOpenAPIClient/api/PetApi.h"
#include "CppRestOpenAPIClient/model/Pet.h"

#include <iostream>
#include <memory>

using namespace org::openapitools::client::api;
using namespace org::openapitools::client::model;

int main()
{
    // ---- Step 1: set up the connection ----
    // ApiConfiguration holds settings like the server's base URL.
    // NOTE: on Linux/Mac, utility::string_t is just std::string, so we
    // use plain string literals (no U("...") macro needed -- that's a
    // Windows-only wide-string helper).
    auto configuration = std::make_shared<ApiConfiguration>();
    configuration->setBaseUrl("https://petstore.swagger.io/v2");

    // ApiClient is the low-level HTTP engine; every *Api class needs one.
    auto apiClient = std::make_shared<ApiClient>(configuration);

    // PetApi exposes the pet-related endpoints as plain C++ methods.
    PetApi petApi(apiClient);

    // ---- Step 2: GET a pet by ID ----
    std::cout << "Looking up pet #1..." << std::endl;
    try
    {
        // getPetById(...) fires off the HTTP request and returns
        // immediately with a "task". .get() blocks until the response
        // arrives (or throws an ApiException on error, e.g. 404).
        std::shared_ptr<Pet> pet = petApi.getPetById(1).get();

        // getName() returns a plain std::string on Linux/Mac -> std::cout works directly.
        std::cout << "Found pet: " << pet->getName() << std::endl;

        // getStatus() returns an ENUM, not a string, so convert it first.
        std::cout << "Status: " << pet->fromStatusEnum(pet->getStatus()) << std::endl;
    }
    catch (const ApiException& ex)
    {
        std::cout << "API error: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    // ---- Step 3: POST a new pet ----
    std::cout << "\nCreating a new pet..." << std::endl;
    try
    {
        auto newPet = std::make_shared<Pet>();
        newPet->setId(12345);
        newPet->setName("Rex");
        newPet->setStatus(Pet::StatusEnum::AVAILABLE);

        // addPet returns pplx::task<void> -- there's nothing to read back,
        // so we just wait for it to finish (or throw).
        petApi.addPet(newPet).get();

        std::cout << "Pet created successfully!" << std::endl;
    }
    catch (const ApiException& ex)
    {
        std::cout << "API error: " << ex.what() << std::endl;
    }

    return 0;
}
