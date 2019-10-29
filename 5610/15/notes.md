
# Lecture 15: Finish tags; Passwords

## Associations Review

Go look at Ecto.Schema module documentation.

 - wheel belongs_to car: The wheel table has a car\_id field, given
   a wheel we can preload the associated car.
 - car has_many wheels: The wheel table has a car\_id field, given
   a car we can preload the wheels.
 - car has_one roof: The roof table has a car\_id field, given a
   car we can preload the roof.
 - has_many through: Allows indirect / many\_to\_many relationships.
 
## Passwords

Problem: User Authentication

 - Lots of apps have user accounts.
 - We want our user accounts to correspond to real people.
 - Specifically, if Alice makes an account, some other user - Mallory -
   shouldn't be able to control that account.
 - When a user logs in - creating a session - we want to authenticate
   that they're the right person.
 - Sadly, that's impossible.
 - Luckly, we can do some stuff that's mostly what we want.

Authentication ideas:
 
 - Link to an already authenticated account - e.g. Google, Facebook, GitHub
   - Still not identifying a person.
   - But we can transfer the identity properties of the external account
     to our user.
 - Link to an email address or phone number.
   - This is exaclty the same as the above.
   - Phone numbers a definitely way worse security-wise.
 - Use a cryptographic public key.
   - Still not a person.
   - Only a person or machine with access to the private key can authenticate
     as the linked user.
 - Use a password.
   - Same as key, just not as secure.

# Solution: Passwords

 - Users select a password when they register.
 - We assume anyone who knows the password is that person.
 - How long a password do we need to require?

## Threat 1: Online Attacks

A person (or program) guesses passwords and tries to log in to the
website with them.

 - Attacker might be able to guess a thousand passwords per second.
 - Assuming a password has random lowercase letters, how long does
   it take to guess a 4 character password?
   - ~5 minutes
 - How about a 6 character password?
   - ~2 days
 - How about an 8 character password?
   - ~7 years

Simple solution: Limit users to 20 login attempts per hour.


## Threat 2: Offline Attacks

The user sends us a password when they register, and we need to be able to check
for the same password when they log in.

Bad Plan #1: Store the password in the database

 - Problem: Anyone who can see our DB can see every user's password.
 - Opportunity: Maybe the user's bank password is the same as the one
   they used for our site (or maybe we're ethical instead).

Bad Plan 2: Store the password encrypted

 - Problem: We need to keep the decryption key where we can
   use it to decrypt to check the password.
 - Now our attacker needs to read two files.

Bad Plan 3: Store a cryptographic hash (e.g. SHA256) in the DB.

 - Now an attacker needs to brute force the hashes before they have
   any passwords.
 - Same problem as mining bitcoin - a GPU can test about a billion
   hashes per second.
 - An 8 character password:
   - Less than 5 minutes
 - A 10 character password is 17 hours.
 - A 12 character password is 1 year.

Bad Plan 4: Store a hash using a password hashing function (e.g. Argon2).

 - This makes time to test a password tunable.
 - You can get to like 100/second.
 - Problem: The attacker can pre-calculate the hashes.
   - This is called a "rainbow tables" attack.

Good-ish Plan: Password hashing function + salt.

 - Hash the password + a random number (the salt)
 - Store the salt with the hash.
 - This breaks rainbow tables.


## Password Requirements:

 - Should your site require that passwords have an uppercase letter,
   a lowercase letter, a korean letter, and an emoji?
   - No.
 - The one requirement you should have is a minimum length.
   - Smallest defensible number is 8.
 - You can check against a table of common passwords and reject them.
 - Should you force users to change their password every 3 months?
   - No.


