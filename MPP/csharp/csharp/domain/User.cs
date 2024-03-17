namespace csharp.domain;

public class User(long id, string name, string email, string password)
    : Entity<long>(id)
{
    public string Name { get; set; } = name;

    public string Email { get; set; } = email;

    public string Password { get; set; } = password;

    public override bool Equals(object? obj)
    {
        if (this == obj)
            return true;

        if (obj == null || GetType() != obj.GetType())
            return false;

        User user = (User)obj;
        return Name == user.Name && Email == user.Email && Password == user.Password;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Name, Email, Password);
    }
}