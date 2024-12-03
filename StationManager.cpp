/*
Sharafat Hussin
11/30/24
*/
#include "StationManager.hpp"
#include <iostream>

// Default Constructor
StationManager::StationManager()
{
    // Initializes an empty station manager
}

// Adds a new station to the station manager
bool StationManager::addStation(KitchenStation *station)
{
    return insert(item_count_, station);
}

// Removes a station from the station manager by name
bool StationManager::removeStation(const std::string &station_name)
{
    for (int i = 0; i < item_count_; ++i)
    {
        if (getEntry(i)->getName() == station_name)
        {
            return remove(i);
        }
    }
    return false;
}

// Finds a station in the station manager by name
KitchenStation *StationManager::findStation(const std::string &station_name) const
{
    Node<KitchenStation *> *searchptr = getHeadNode();
    while (searchptr != nullptr)
    {
        if (searchptr->getItem()->getName() == station_name)
        {
            return searchptr->getItem();
        }
        searchptr = searchptr->getNext();
    }
    return nullptr;
}

// Moves a specified station to the front of the station manager list
bool StationManager::moveStationToFront(const std::string &station_name)
{
    // First, make sure the station exists
    if (findStation(station_name) == nullptr)
    {
        return false;
    }

    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name)
    {
        return true;
    }

    Node<KitchenStation *> *searchptr = getHeadNode();
    while (searchptr != nullptr)
    {
        if (searchptr->getItem()->getName() == station_name)
        {
            // Make a copy of the station
            KitchenStation *station = searchptr->getItem();

            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);

            // Insert the station at the front
            insert(0, station);

            return true; // Exit after moving the station
        }

        searchptr = searchptr->getNext(); // Move to the next node
    }

    return false;
}

int StationManager::getStationIndex(const std::string &name) const
{
    Node<KitchenStation *> *searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr)
    {
        if (searchptr->getItem()->getName() == name)
        {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

// Merges the dishes and ingredients of two specified stations
bool StationManager::mergeStations(const std::string &station_name1, const std::string &station_name2)
{
    KitchenStation *station1 = findStation(station_name1);
    KitchenStation *station2 = findStation(station_name2);
    if (station1 && station2)
    {
        // take all the dishes from station2 and add them to station1
        for (Dish *dish : station2->getDishes())
        {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock())
        {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

// Assigns a dish to a specific station
bool StationManager::assignDishToStation(const std::string &station_name, Dish *dish)
{
    KitchenStation *station = findStation(station_name);
    if (station)
    {
        return station->assignDishToStation(dish);
    }
    return false;
}

// Replenishes an ingredient at a specific station
bool StationManager::replenishIngredientAtStation(const std::string &station_name, const Ingredient &ingredient)
{
    KitchenStation *station = findStation(station_name);
    if (station)
    {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

// Checks if any station in the station manager can complete an order for a specific dish
bool StationManager::canCompleteOrder(const std::string &dish_name) const
{
    Node<KitchenStation *> *searchptr = getHeadNode();
    while (searchptr != nullptr)
    {
        if (searchptr->getItem()->canCompleteOrder(dish_name))
        {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

// Prepares a dish at a specific station if possible
bool StationManager::prepareDishAtStation(const std::string &station_name, const std::string &dish_name)
{
    KitchenStation *station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name))
    {
        return station->prepareDish(dish_name);
    }
    return false;
}

/**
 * Retrieves the current dish preparation queue.
 * @return A copy of the queue containing pointers to Dish objects.
 * @post: The dish preparation queue is returned unchanged.
 */

std::queue<Dish *> StationManager::getDishQueue()
{
    return (dish_queue_);
}

/**
* Retrieves the list of backup ingredients.
* @return A vector containing Ingredient objects representing backup
supplies.
* @post: The list of backup ingredients is returned unchanged.
*/

std::vector<Ingredient> StationManager::getBackupIngredients()
{
    return (backup_ingredients_);
}

/**
* Sets the current dish preparation queue.
* @param dish_queue A queue containing pointers to Dish objects.
* @pre: The dish_queue contains valid pointers to dynamically allocated
Dish objects.
* @post: The dish preparation queue is replaced with the provided
queue.
*/

void StationManager::setDishQueue(std::queue<Dish *> &dish_queue)
{
    dish_queue_.swap(dish_queue);
}

/**
* Sets the backup ingredients list.
* @param backup_ingredients A vector of Ingredient objects representing
backup supplies.
* @pre: The backup_ingredients vector contains valid Ingredient
objects.
* @post: Replaced the backup Ingrediets
Task 2: Implement the addDishToQueue Functions
Implement two overloaded addDishToQueue functions in StationManager :
Task 3: Implement the prepareNextDish Function
Implement the prepareNextDish function in StationManager :
Task 4: Implement the displayDishQueue Function.
*/
void StationManager::setBackupIngredients(const std::vector<Ingredient> &backup_ingredients)
{
    backup_ingredients_ = backup_ingredients;
}

/**
 * Adds a dish to the preparation queue without dietary accommodations.
 * @param dish A pointer to a dynamically allocated Dish object.
 * @pre: The dish pointer is not null.
 * @post: The dish is added to the end of the queue.
 */

void StationManager::addDishToQueue(Dish *dish)
{
    dish_queue_.push(dish);
}

/**
* Adds a dish to the preparation queue with dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @param request A DietaryRequest object specifying dietary
accommodations.
* @pre: The dish pointer is not null.
* @post: The dish is adjusted for dietary accommodations and added to
the end of the queue.
*/

void StationManager::addDishToQueue(Dish *dish, Dish::DietaryRequest &request)
{
    dish->dietaryAccommodations(request);
    dish_queue_.push(dish);
}

/**
 * Prepares the next dish in the queue if possible.
 * @pre: The dish queue is not empty.
 * @post: The dish is processed and removed from the queue.
 * If the dish cannot be prepared, it stays in the queue
 * @return: True if the dish was prepared successfully; false otherwise.
 */
bool StationManager::prepareNextDish()
{
    if(dish_queue_.empty()){
        return(false);
    }
    Dish *dish = dish_queue_.front();
    Node<KitchenStation *> *searchptr = getHeadNode();
    while (searchptr != nullptr)
    {
        std::string station_name = searchptr->getItem()->getName();
        if (prepareDishAtStation(station_name, dish->getName()))
        {
            dish_queue_.pop();
            return true;
        }
       searchptr=searchptr->getNext();
    }
    return false;
}

/**
* Displays all dishes in the preparation queue.
* @pre: None.
* @post: Outputs the names of the dishes in the queue in order (each name
is on its own line).
*/

void StationManager::displayDishQueue()
{
    std::queue<Dish *> dishes = getDishQueue();
    while (!dishes.empty())
    {
        std::cout << dishes.front()->getName() << "\n";
        dishes.pop();
    }
}

/**
 * Clears all dishes from the preparation queue.
 * @pre: None.
 * @post: The dish queue is emptied and all allocated memory is freed.
 */
void StationManager::clearDishQueue()
{
    while (!dish_queue_.empty())
    {
        dish_queue_.pop();
    }
}

/**
* Replenishes a specified ingredient at a given station from the backup stock by a defined quantity.
 * 
 * @param station_name A string representing the name of the station.
 * @param ingredient_name A string representing the name of the ingredient to replenish.
 * @param quantity An integer specifying the amount of the ingredient to add.
 * 
 * @pre None.
 * @post 
 * If the ingredient exists in the backup stock and there is sufficient quantity, the specified amount is added to the station's ingredient stock. 
 * The function then returns true.
 * The quantity of the ingredient in the backup stock is decreased by the specified amount.
 * If the backup stock quantity of the ingredient reaches zero, the ingredient is removed from the backup stock entirely.
 * If the backup stock does not have enough of the ingredient, or if the ingredient or station cannot be found, the function returns false.
 * 
 * @return 
 *  True if the ingredient was successfully replenished from the backup stock.
 * False if the operation could not be completed.
 * 
 * Note: This function works in conjunction with `addBackupIngredient` and `clearBackupIngredients`.
 *
*/
bool StationManager::replenishStationIngredientFromBackup(const std::string& station_name, const std::string& ingredient_name, int quantity)
{
        if(!findStation(station_name)){
        return(false);
    }
    for(size_t i=0; i<backup_ingredients_.size();i++)
    {

       if (backup_ingredients_[i].name == ingredient_name && backup_ingredients_[i].quantity >= quantity)
        {
            Ingredient new_ingredient = backup_ingredients_[i];
            new_ingredient.quantity = quantity;
            backup_ingredients_[i].quantity -= quantity;
            if(backup_ingredients_[i].quantity == 0){
                backup_ingredients_.erase(backup_ingredients_.begin() + i);
            }
            this->replenishIngredientAtStation(station_name, new_ingredient);
            return true;
        }
    }
    return false;
}

/**
* Sets the backup ingredients stock with the provided list of ingredients.
* @param ingredients A vector of Ingredient objects to set as the backup
stock.
* @pre None.
* @post The backup_ingredients_ vector is replaced with the provided
ingredients.
* @return True if the ingredients were added; false otherwise.
*/

bool StationManager::addBackupIngredients(const std::vector<Ingredient>& ingredients)
{
    /*if (ingredients.empty())
    {
        return false;    
    }*/
    backup_ingredients_ = ingredients;
        return true;
    /*for(auto& ingredient: ingredients){
        if(!addBackupIngredient(ingredient)){
            return(false);
        }
    }
    return(true);*/
}

/**
* Adds a single ingredient to the backup ingredients stock.
* @param ingredient An Ingredient object to add to the backup stock.
* @pre None.
* @post If the ingredient already exists in the backup stock, its quantity
is increased by the ingredient's quantity.
* If the ingredient does not exist, it is added to the backup stock.
* @return True if the ingredient was added; false otherwise.
*/

bool StationManager::addBackupIngredient(const Ingredient& ingredient)
{
    
    for (auto& i : backup_ingredients_)
    {
        if (i.name == ingredient.name)
        {
            i.quantity += ingredient.quantity;
            return true;
        }
    }
    backup_ingredients_.push_back(ingredient);
    return true;
}

/**
 * Empties the backup ingredients vector
 * @post The backup_ingredients_ private member variable is empty.
 */

void StationManager::clearBackupIngredients()
{
    backup_ingredients_.clear();
}

/**
* Processes all dishes in the queue and displays detailed results.
* @pre: None.
* @post: All dishes in the queue are processed, and detailed information is displayed
 
    * as per the format specified in the requirements. This includes:
    * - Station replenishments.
    * - Preparation results for each dish.
    * If a dish cannot be prepared, even after replenishing ingredients, it 
    * remains in the queue in its original order.
    * If multiple dishes cannot be prepared, they will stay in the queue 
    *  maintaining the same order as before.
    */
void StationManager::processAllDishes() {
    std::queue<Dish *> dishes;
   
    while (!dish_queue_.empty()) {
        Dish *dish = dish_queue_.front();
        bool prepared = false;
        Node<KitchenStation *> *currentNode = this->getHeadNode();

        std::cout << "PREPARING DISH: " << dish->getName() << std::endl;

        while (currentNode != nullptr) {
            KitchenStation *station = currentNode->getItem();
            currentNode = currentNode->getNext();
            
            std::cout << station->getName() << " attempting to prepare " << dish->getName() << "..." << std::endl;
            
            bool found = false;
            for (auto item : station->getDishes()) {
                if (dish->getName() == item->getName()) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cout << station->getName() << ": Dish not available. Moving to next station..." << std::endl;
                continue;
            }

            prepared = this->prepareDishAtStation(station->getName(), dish->getName());
            if (prepared) {
                std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
                dish_queue_.pop();
                break;
            }

            int diff = 0;
            std::string name = "";
            for (const Ingredient &ingredient : dish->getIngredients()) {
                for (const Ingredient &stock_ingredient : station->getIngredientsStock()) {
                    if (stock_ingredient.name == ingredient.name && stock_ingredient.quantity < ingredient.required_quantity) {
                        diff = ingredient.required_quantity - stock_ingredient.quantity;
                        name = ingredient.name;
                        break;
                    }
                }
                if (!name.empty()) {
                    break;
                }
            }

            if (!name.empty()) {
                std::cout << station->getName() << ": Insufficient ingredients. Replenishing ingredients..." << std::endl;
                bool replenished = replenishStationIngredientFromBackup(station->getName(), name, diff);
                
                if (replenished) {
                    std::cout << station->getName() << ": Ingredients replenished." << std::endl;
                    prepared = this->prepareDishAtStation(station->getName(), dish->getName());
                    if (prepared) {
                        std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
                        dish_queue_.pop();
                        break;
                    } else {
                        std::cout << station->getName() << ": Dish not available. Moving to next station..." << std::endl;
                    }
                } else {
                    std::cout << station->getName() << ": Unable to replenish ingredients. Failed to prepare " << dish->getName() << "." << std::endl;
                }
            }
        }

        if (!prepared) {
            std::cout << dish->getName() << " was not prepared." << std::endl;
            dishes.push(dish);
            dish_queue_.pop();
        }
    }

    dish_queue_ = dishes;
    std::cout << "All dishes have been processed." << std::endl;
}
