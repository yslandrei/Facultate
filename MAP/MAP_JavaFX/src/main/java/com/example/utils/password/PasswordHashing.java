package com.example.utils.password;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class PasswordHashing {

    /**
     * Hashes the given password using SHA-256.
     *
     * @param plainPassword The password to be hashed.
     * @return The hashed password.
     */
    public static String hashPassword(String plainPassword) {
        try {
            MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = messageDigest.digest(plainPassword.getBytes());

            // Convert the byte array to a hexadecimal string
            StringBuilder stringBuilder = new StringBuilder();
            for (byte b : hashedBytes) {
                stringBuilder.append(String.format("%02x", b));
            }

            return stringBuilder.toString();
        } catch (NoSuchAlgorithmException e) {
            // Handle the exception (e.g., log it or throw a runtime exception)
            throw new RuntimeException("Error hashing password.", e);
        }
    }

}
