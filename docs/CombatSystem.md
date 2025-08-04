# Combat system

## Description
System handling combat interactions between entites. It uses a component-based architecture with layered damage flow : block -> armor -> health. Ther system supports mechanics such as:
- Attack initiation and cooldowns
- Damage calculation and application
- Health managment
- Targeting
- Defense mechanism (block and armor)
- Interrupts attacks when blocking is active

## Components

### AttackComponent
__Base class for attack components__
- Manage attack timing and damage application
- Store selected target
- Handles range check
- Parameters:
	- `startupTime`: Wind-up before attack
	- `cooldown`: Time between two attacks
	- `damage`: Base attack damage
	- `range`: Maximum effective attack distance
- Methods:
	- `StartAttack()` : Initiate startup/cooldown timers if not blocking
	- `Update(float)` : Updating timers. Interrupts atack if blocking. Calls `ProcessAttack()` when startup completes
	- `ProcessAttack()` : Verifies target in range, then applies damage to target's Block/Armor/Health components (in order) if cthey exist
	- Getters/setters for parameters, target and timers

Derived classes:
- `AIAttackComponent`
- `PlayerAttackComponent`

### AIAttackComponent
__Derived from AttackComponent for AI-controlled actors__

Overrides `Update()` method - calls base `Update()`, then initiates attack if:
1. Attack is off cooldown
2. Target is visible
3. Target is in range

### PlayerAttackComponent
__Derived from AttackComponent for player-controlled actors__

Uses Observer pattern to recieve attack input notifications. When notified:
1. Verifies attack is off cooldown
2. Selects closest non-player actor
3. Calls `StartAttack()`

### BlockComponent
__Input-dependent defense component (first in damage flow)__
- Slows character when active
- Renders icon when active
- Prevents new attack and interrupts ongoing attacks
- Parameters:
	- `damageReduction` : Damage absorbtion rate (0.0-1.0)
	- `speedCoefficient` : Movement speed multiplier when blocking
	- `iconCenterOffset` : Icon position relative to entity
	- `iconRadius` : Icon size
	- `iconColor` : Icon color
- Methods:
	- `Update(float)` : Syncs state with `InputComponent`, updates movement speed in `MovementComponent`.
	- `Render()` : Draws icon when blocking
	- `ApplyDamage(float)` : Returns reduced damage if blocking, full damage otherwise
    - `GetIsBlocking()`: Returns current blocking state

### ArmorComponent
__Passive defense through damage absorption (second in damage flow)__
- Tracks current/maximum armor points
- Parameters:
	- `maxArmorPoints` : Total armor capacity
	- `damageReduction` : Damage absorption rate (0.0-1.0)
- Methods:
	- `ApplyDamage(float)` : Absorbs damage proportionally, reduces armor points, returns remaining damage
	- `IncreaseArmorPoints(float)` : Restores armor, returns excess restoration
	- `IsNotBroken()` : Checks if armor points > 0
	- Getters/setters for parameters and current armor

### HealthComponent
__Core health management (last in damage flow)__
- Tracks current/maximum health points
- Parameters:
	- `maxHealth` : Maximum health points
- Methods:
	- `DecreaseHealth(float)` : Reduces health, returns overkill damage
	- `IncreaseHealth(float)` : Restores health, returns overheal amount
	- `IsAlive()` : Returns true if health > 0

## Usage sample
~~~cpp
auto player = MaxrEngine::GameWorld::Instance()->CreateGameObject("Player");
Roguelike::AttackComponent::Parameters playerAttackParameters = {
    .startupTime = 0.2F,
    .cooldown = 2.0F,
    .damage = 30.0F,
    .range = 110.0F};
player->AddComponent<Roguelike::PlayerAttackComponent>(
    playerAttackParameters);
player->AddComponent<Roguelike::HealthComponent>(100.f);
Roguelike::BlockComponent::Parameters playerBlockParameters = {
    .damageReduction = 1.0F,
    .speedCoefficient = 0.1F,
    .iconCenterOffset = {-35.0F, 30.0F},
    .iconRadius = 6.0F,
    .iconColor = sf::Color(0, 255, 0)};
player->AddComponent<Roguelike::BlockComponent>(playerBlockParameters);
~~~