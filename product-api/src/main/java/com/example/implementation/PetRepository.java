package com.example.implementation;

import com.example.implementation.PetEntity;
import org.springframework.data.jpa.repository.JpaRepository;

public interface PetRepository
        extends JpaRepository<PetEntity, Integer> {
}