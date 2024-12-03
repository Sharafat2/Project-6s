/*
Sharafat Hussin
11/30/24
*/
#ifndef STATIONMANAGER_HPP
#define STATIONMANAGER_HPP

#include "LinkedList.hpp"
#include "KitchenStation.hpp"
#include "Dish.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include <string>
#include<queue>

class StationManager : public LinkedList<KitchenStation*> {
public:
    /**
     * Default Constructor
     * @post: Initializes an empty stationn manager.
     */
    StationManager();


    /**
 * Adds a new kitchen station to the station manager's list.
 *
 * @param station Pointer to the `KitchenStation` object to be added.
 *
 * @post The station is inserted into the station manager's linked list of stations.
 */

    bool addStation(KitchenStation* station);

    /**
     *  Removes a station from the station manager by its name.
     * @param station_name station- The name of the station to be removed.
     * @post: Removes the station from the list and deallocates it.
     * @return: True if the station was found and removed; false otherwise.
     */
    bool removeStation(const std::string& station_name);

    /**
     * Finds a station in the station manager by name.
     * @param station_name A string representing the station's name.
     * @return: A pointer to the KitchenStation nullptr otherwise.
     */
    KitchenStation* findStation(const std::string& station_name) const;

    /**
     * Moves a specified station to the front of the station manager list.
     * @param station_name A string representing the station's name.
     * @post: The station is moved to the front of the list if it exists.
     * @return: True if the station was found and moved; false otherwise.
     */
    bool moveStationToFront(const std::string& station_name);

    /**
     * Merges the dishes and ingredients of two specified stations.
     * @param station_name1 The name of the first station.
     * @param station_name2 The name of the second station.
     * @post: The second station is removed from the list, and its contents are added to the first station.
     * @return: True if both stations were found and merged; false otherwise.
     */
    bool mergeStations(const std::string& station_name1, const std::string& station_name2);

    /**
     * Assigns a dish to a specific station.
     * @param station_name A string representing the station's name.
     * @param dish A pointer to a Dish object.
     * @post: Assigns the dish to the specified station.
     * @return: True if the station was found and the dish was assigned; false otherwise.
     */
    bool assignDishToStation(const std::string& station_name, Dish* dish);

    /**
     * Replenishes an ingredient at a specific station.
     * @param station_name A string representing the station's name.
     * @param ingredient An Ingredient object.
     * @post: Replenishes the ingredient stock at the specified station.
     * @return: True if the station was found and the ingredient was replenished; false otherwise.
     */
    bool replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient);

    /**
     * Checks if any station in the station manager can complete an order for a specific dish.
     * @param dish_name A string representing the name of the dish.
     * @return: True if any station can complete the order; false otherwise.
     */
    bool canCompleteOrder(const std::string& dish_name) const;

    /**
     * Prepares a dish at a specific station if possible.
     * @param station_name A string representing the station's name.
     * @param dish_name A string representing the name of the dish.
     * @post: If the dish can be prepared, reduces the quantities of the used ingredients at the station.
     * @return: True if the dish was prepared successfully; false otherwise.
     */
    bool prepareDishAtStation(const std::string& station_name, const std::string& dish_name);

    /**
* Retrieves the current dish preparation queue.
* @return A copy of the queue containing pointers to Dish objects.
* @post: The dish preparation queue is returned unchanged.
*/

std::queue<Dish*> getDishQueue();

/**
* Retrieves the list of backup ingredients.
* @return A vector containing Ingredient objects representing backup
supplies.
* @post: The list of backup ingredients is returned unchanged.
*/

std::vector<Ingredient> getBackupIngredients();

/**
* Sets the current dish preparation queue.
* @param dish_queue A queue containing pointers to Dish objects.
* @pre: The dish_queue contains valid pointers to dynamically allocated
Dish objects.
* @post: The dish preparation queue is replaced with the provided
queue.
*/

void setDishQueue(std::queue<Dish*>& dish_queue);

/**
* Sets the backup ingredients list.
* @param backup_ingredients A vector of Ingredient objects representing
backup supplies.
* @pre: The backup_ingredients vector contains valid Ingredient
objects.
* @post: The list of backup ingredients is replaced with the provided
Task 2: Implement the addDishToQueue Functions
Implement two overloaded addDishToQueue functions in StationManager :
Task 3: Implement the prepareNextDish Function
Implement the prepareNextDish function in StationManager :
Task 4: Implement the displayDishQueue Function
vector.
*/
void setBackupIngredients(const std::vector<Ingredient>& backup_ingredients);

/**
* Adds a dish to the preparation queue without dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @pre: The dish pointer is not null.
* @post: The dish is added to the end of the queue.
*/

void addDishToQueue( Dish* dish);

/**
* Adds a dish to the preparation queue with dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @param request A DietaryRequest object specifying dietary
accommodations.
* @pre: The dish pointer is not null.
* @post: The dish is adjusted for dietary accommodations and added to
the end of the queue.
*/

void addDishToQueue( Dish* dish, Dish::DietaryRequest& request);

/**
* Prepares the next dish in the queue if possible.
* @pre: The dish queue is not empty.
* @post: The dish is processed and removed from the queue.
* If the dish cannot be prepared, it stays in the queue
* @return: True if the dish was prepared successfully; false otherwise.
*/

bool prepareNextDish();

/**
* Displays all dishes in the preparation queue.
* @pre: None.
* @post: Outputs the names of the dishes in the queue in order (each name
is on its own line).
*/

void displayDishQueue();

/**
* Clears all dishes from the preparation queue.
* @pre: None.
* @post: The dish queue is emptied and all allocated memory is freed.
*/
void clearDishQueue();

/**
* Replenishes a specific ingredient at a given station from the backup
ingredients stock by a specified quantity.
* @param station_name A string representing the name of the station.
* @param ingredient_name A string representing the name of the ingredient
to replenish.
* @param quantity An integer representing the amount to replenish.
* @pre None.
* @post If the ingredient exists in the backup ingredient stock and has enough quantity, it is added to the station's ingredient stock by the specified amount, and the function returns true.

The quantity of the ingredient in the backup stock is decreased by the specified amount.
If the backup stock's quantity of the ingredient reaches zero (meaning it's depleted), the ingredient is removed from the backup stock.
If the backup stock does not have enough of the ingredient, or if the ingredient or station cannot be found, the function returns false.


* @return True if the ingredient was replenished from backup; false
Implemented both
addBackupIngredient
and
clearBackupIngredients
*/

bool replenishStationIngredientFromBackup(const std::string& station_name,const std::string& ingredient_name, int quantity );

/**
* Sets the backup ingredients stock with the provided list of ingredients.
* @param ingredients A vector of Ingredient objects to set as the backup
stock.
* @pre None.
* @post The backup_ingredients_ vector is replaced with the provided
ingredients.
* @return True if the ingredients were added; false otherwise.
*/

bool addBackupIngredients(const std::vector<Ingredient>& ingredients);

/**
* Adds a single ingredient to the backup ingredients stock.
* @param ingredient An Ingredient object to add to the backup stock.
* @pre None.
* @post If the ingredient already exists in the backup stock, its quantity
is increased by the ingredient's quantity.
* If the ingredient does not exist, it is added to the backup stock.
* @return True if the ingredient was added; false otherwise.
*/

bool addBackupIngredient(const Ingredient& ingredient);

/**
* Empties the backup ingredients vector
* @post The backup_ingredients_ private member variable is empty.
*/

void clearBackupIngredients();

/**
 * Processes all dishes in the queue and displays detailed results.
 *
 * @pre: None.
 *
 * @post: Attempts to process each dish in the queue, displaying detailed information—including station replenishments and preparation results—in accordance with the specified format.
 * If a dish cannot be prepared even after attempting to replenish ingredients, it remains in the queue at its original position.
 * In other words, if multiple dishes cannot be prepared, they will stay in the queue maintaining their initial order.
 */


void processAllDishes();

private:
    // helper function to get index of a station by name
    int getStationIndex(const std::string& station_name) const;
    std::queue<Dish*> dish_queue_;
    std::vector<Ingredient> backup_ingredients_;
};

#endif // STATIONMANAGER_HPP
