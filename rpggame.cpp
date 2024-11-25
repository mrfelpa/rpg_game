#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <thread>
#include <chrono>

#define MAX_HEALTH 100
#define ITEM_HEALTH_BOOST 20

typedef struct {
    char name[50];
    int health;
    int strength;
} Character;

typedef struct {
    char name[50];
    int health;
    int strength;
} Enemy;

typedef struct {
    char name[50];
    int healthBoost;
} Item;

void introduction();
void explore(Character *player);
void interact(Character *player);
void battle(Character *player, Enemy *enemy);
void findItem(Character *player);
void displayStatus(Character *player);
char getUserChoice();
void handleInvalidChoice();

int main() {
    Character player;
    strcpy(player.name, "Hero");
    player.health = MAX_HEALTH;
    player.strength = 10;

    introduction();

    while (player.health > 0) {
        displayStatus(&player);
        printf("\nChoose an action: (e) Explore, (i) Interact, (q) Quit: ");
        char choice = getUserChoice();

        switch (choice) {
            case 'e':
                explore(&player);
                break;
            case 'i':
                interact(&player);
                break;
            case 'q':
                printf("Exiting the game...\n");
                return 0;
            default:
                handleInvalidChoice();
        }
    }

    printf("You have been defeated! Game Over.\n");
    return 0;
}

void introduction() {
    printf("Welcome to the Text RPG!\n");
    printf("You are a hero seeking adventures!\n");
}

void displayStatus(Character *player) {
    printf("\n--- Player Status ---\n");
    printf("Name: %s\n", player->name);
    printf("Health: %d\n", player->health);
}

char getUserChoice() {
    char choice;

    if (scanf(" %c", &choice) != 1) {
        // Handle input error
        fprintf(stderr, "Error reading input.\n");
        exit(EXIT_FAILURE);
    }

    return choice;
}

void handleInvalidChoice() {
    printf("Invalid choice! Try again.\n");
}

void explore(Character *player) {
    printf("You venture into the forest...\n");

    srand(time(NULL));
    int encounter = rand() % 2; // 0 for item, 1 for enemy

    if (encounter == 0) {
        findItem(player);
    } else {
        Enemy enemy = {"Goblin", 50, 5};
        printf("You encounter a wild %s!\n", enemy.name);
        battle(player, &enemy);
    }
}

void findItem(Character *player) {
    Item item = {"Healing Potion", ITEM_HEALTH_BOOST};

    printf("You found a %s!\n", item.name);

    player->health += item.healthBoost;

    if (player->health > MAX_HEALTH) {
        player->health = MAX_HEALTH;
    }

    printf("Your health has increased by %d! Current Health: %d\n", item.healthBoost, player->health);
}

void interact(Character *player) {
    printf("You meet a mysterious traveler...\n");

    char choice;
    printf("Do you want to (a) Ask for a quest or (b) Trade? ");

    choice = getUserChoice();

    if (choice == 'a') {
        printf("The traveler offers you a quest to defeat a nearby monster!\n");
    } else if (choice == 'b') {
        printf("The traveler has nothing to trade right now.\n");
    } else {
        handleInvalidChoice();
    }
}

void battle(Character *player, Enemy *enemy) {
    printf("A battle begins with %s!\n", enemy->name);

    while (player->health > 0 && enemy->health > 0) {
        enemy->health -= player->strength;
        printf("%s attacks %s! %s's health: %d\n", player->name, enemy->name, enemy->name, enemy->health);

        if (enemy->health <= 0) {
            printf("%s has been defeated!\n", enemy->name);
            return;
        }

        player->health -= enemy->strength;
        printf("%s attacks %s! Your health: %d\n", enemy->name, player->name, player->health);

        if (player->health <= 0) {
            printf("%s has been defeated!\n", player->name);
            return;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
