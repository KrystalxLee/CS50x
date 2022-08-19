-- Keep a log of any SQL queries you execute as you solve the mystery.

--Find the ID that corresponds to the date and location of the crime
SELECT id from crime_scene_reports WHERE year = 2021 AND day = 28 AND month = 7 AND street = "Humphrey Street"
--ID 295 --> Theft of duck took place at 10:15 AM at Humphrey Street bakery. Interviews were conducted today with 3 witnesses who were present at the time - each of their interview transcripts mention the bakery
--ID 297 -->  Littering took place at 16:36. No known witnesses.


--search bakery security logs for license plate of thief/accomplice entering and existing the bakery at the date/time of theft
SELECT id, hour, minute, activity, license_plate FROM bakery_security_logs WHERE hour = 10 AND year = 2021 AND month = 7 AND day = 28;
--thief entered before 10:15 AM
--thief exit sometime between 10:15 AM and 10:25 AM


SELECT id, name, transcript FROM interviews where year = 2021 AND month = 7 AND day = 28;
--161 Ruth
--Sometime within ten minutes of the theft, I saw the thief get into a car in the
--bakery parking lot and drive away. If you have security footage from the bakery parking lot,
--you might want to look for cars that left the parking lot in that time frame

-- 162 Eugene
-- I don't know the thief's name, but it was someoe I recognized. Earlier this morning, before I arried at Emma's bakery, I was walking by the ATM on Leggett Street
-- and saw the thief there withdrawing some money.

--163 Raymond
--As the thief was leaving the bakery, they called someone who talked to them for less
--than a minute. In the call, I heard the thief say that they were planning to take the earliest flight
--out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.


SELECT id, account_number, transaction_type, amount FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street";
--gives info on account number and withdrawl amounts for the date and location (Leggett Street)

SELECT id, origin_airport_id, destination_airport_id, hour, minute FROM flights WHERE year = 2021 AND month = 7 AND day = 29;
--accomplice bought earliest flight for "tomorrow" AKA july 29th 2021
--earliest flight hour 8:20 AM
--origin airport id = 8
--destination airport id = 4
--flight ID = 36

SELECT full_name, city FROM airports WHERE id = 4;
--thief went to New York City on July 29th, 2021.

SELECT passport_number, seats FROM passengers WHERE flight_id = 36;
--returns list of passports for the potential burglar

SELECT person_id, creation_year, account_number FROM bank_accounts WHERE account_number = (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street");
--person id 467400
--creation year 2014
--account number 28500762

SELECT name, phone_number, passport_number, license_plate FROM people WHERE id = 467400;
--name Luca
--phone number 389 555 5198
--passport number = 849633585
--license plate 4328GD8

SELECT id, caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 ADN day = 28 AND duration <60;
--Luca's number is the receiver
--corresponding caller number 609 555 5876

SELECT name, passport_number, license_plate FROM people WHERE phone_number = "(609) 555-5876";
--Accomplice = Kathryn
--Passport 6121106406
--License plate 4ZY7I8T
