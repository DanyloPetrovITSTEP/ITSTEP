/*class Character
{
    public event Action<int, int>? OnHealthChanged;
    public event Action<int, int>? OnDead;

    private int _health;

    public int Health
    { 
        get => _health;
        set
        {
            if (_health == value) return;

            int oldHealth = _health;
            _health = value;

            OnHealthChanged?.Invoke(oldHealth, _health);
            if (_health <= 0) OnDead?.Invoke(_health, _health);
        }
    }

    public void Damage(int damage)
    {
        Health -= damage; 
    }
}*/