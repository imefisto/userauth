# userauth
Library for User Authentication

Use cases:

Login
=====

```cpp
LogIn useCase{SomeUserRepository};
auto response = useCase.tryToIdentify("some-username", "some-password");
```

No matter the validation result, response.user will have an optional<user> instance.

response.success will be true if the user with "some-username" exists in the repository and the password validates ok. Otherwise it will be false.

Signup (TODO)

Recovery password (TODO)

Change password (TODO)
