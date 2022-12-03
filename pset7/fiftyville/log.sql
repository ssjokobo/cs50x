-- Keep a log of any SQL queries you execute as you solve the mystery.

-- See some initial information from the report scoping with dates and street.
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery.

-- Look for interviewees on the crime date with mention of the bakery.
SELECT name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- | Ruth    |
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

SELECT name
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute < 30
ORDER BY name;

-- | Eugene  |
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and
-- saw the thief there withdrawing some money.

SELECT name
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE atm_transactions.year = 2021
    AND atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw'
ORDER BY name;

-- | Raymond |
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT name
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
ORDER BY name;

-- | Emma    |
-- I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.

SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28;

-- Noone talked that long, probably pretending to be talking on a phone.

-- Combine all of the 3 large queries.
SELECT name
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute < 30
    AND name IN(
    SELECT name
    FROM atm_transactions
    JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
    JOIN people ON bank_accounts.person_id = people.id
    WHERE atm_transactions.year = 2021
        AND atm_transactions.month = 7
        AND atm_transactions.day = 28
        AND atm_transactions.atm_location = 'Leggett Street'
        AND atm_transactions.transaction_type = 'withdraw'
        AND name IN(
        SELECT name
        FROM phone_calls
        JOIN people ON phone_calls.caller = people.phone_number
        WHERE year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60
    )
);

-- Only 2 names appeared: Bruce and Diana.

-- Check info for Bruce and Diana, see if there's any other person with the same name.
SELECT * FROM people WHERE name = 'Bruce' OR name = 'Diana';

-- These are unique names.

-- Finding the earliest flight on the next day (7/29/2021)
SELECT *
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2021
    AND month = 7
    AND day = 29
ORDER BY hour;

-- Ealiest flight id = 36 and 43

-- Finding passengers
SELECT *
FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36
    AND (name = 'Bruce'
    OR name = 'Diana');

-- Found Bruce. The theif is Bruce.

-- Finding the destination
SELECT *
FROM flights
JOIN airports ON flights.destination_airport_id = airports.id
WHERE flights.id = 36;

-- The city destination is New York City.

-- Get Bruce's phone number.
SELECT phone_number FROM people WHERE name = 'Bruce';

-- Bruce's number is (367) 555-5533.

-- Find who did Bruce talk to
SELECT name
FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller = '(367) 555-5533';

-- The accomplice is Robin.