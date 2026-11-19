package com.example.api;
import com.example.model.Pet;
import com.example.api.PetApiDelegate;
import com.example.implementation.PetEntity;
import com.example.implementation.PetRepository;

import java.util.List;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

@Service
public class PetApiDelegateImpl implements PetApiDelegate {

    private final PetRepository petRepository;

    public PetApiDelegateImpl(PetRepository petRepository) {
        this.petRepository = petRepository;
    }

    @Override
    public ResponseEntity<Pet> getPetById(Long petId) {

        // YOUR CODE GOES HERE

        Pet pet = new Pet();
        pet.setId(petId);
        pet.setName("My Test Pet");
        pet.setStatus(Pet.StatusEnum.AVAILABLE);

        return ResponseEntity.ok(pet);
    }

    @Override
    public ResponseEntity<Void> addPet(Pet body) {

        // Read fields from the request
        Long id = body.getId();
        String name = body.getName();
        String status = body.getStatus() != null
                ? body.getStatus().getValue()
                : null;

        // Display received data
        System.out.println("Received new pet:");
        System.out.println("ID: " + id);
        System.out.println("Name: " + name);
        System.out.println("Status: " + status);

        // Convert API model into database entity
         PetEntity entity = new PetEntity();

            entity.setName(body.getName());

            if (body.getStatus() != null) {
                entity.setStatus(body.getStatus().getValue());
            }

    // Save the entity in PostgreSQL
    PetEntity savedPet = petRepository.save(entity);

    System.out.println("Saved pet with ID: " + savedPet.getId());

    return ResponseEntity.status(HttpStatus.CREATED).build();

    }

    @Override
    public ResponseEntity<Void> deletePet(Long petId, String apiKey) {

        // Display received data
        System.out.println("Deleted pet with ID: " + petId);

        // TODO: Remove the pet from your database

        return ResponseEntity.status(HttpStatus.OK).build();
    }

    @Override
    public ResponseEntity<Void> updatePet(Pet body) {

        // Read fields from the request
        Long id = body.getId();
        String name = body.getName();
        String status = body.getStatus() != null
                ? body.getStatus().getValue()
                : null;

        // Display received data
        System.out.println("Updated pet:");
        System.out.println("ID: " + id);
        System.out.println("Name: " + name);
        System.out.println("Status: " + status);

        // TODO: Update the pet in your database

        return ResponseEntity.status(HttpStatus.OK).build();
    }

    @Override
    public ResponseEntity<Void> updatePetWithForm(Long petId, String name, String status) {

        // Display received data
        System.out.println("Updated pet with ID: " + petId);
        System.out.println("New Name: " + name);
        System.out.println("New Status: " + status);

        // TODO: Update the pet in your database

        return ResponseEntity.status(HttpStatus.OK).build();
    }

    @Override 
    public ResponseEntity<List<Pet>> findPetsByStatus(List<String> status) {

        // Display received data
        System.out.println("Finding pets with status: " + status);
        return ResponseEntity.ok(List.of( 
            new Pet().id(1L).name("Doggie").status(Pet.StatusEnum.AVAILABLE),
            new Pet().id(2L).name("Kitty").status(Pet.StatusEnum.AVAILABLE)
        ));
    }

}
