#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checkLoyalty.c"
#include "queue.c"

typedef struct Customer {
  char name[50];
  char phoneNo[20];
  double spendings;
} Customer;

double updateCustomerSpendings(char *fileName, char *targetPhoneNo,
                               double newSpendings) {
  FILE *file = fopen(fileName, "r+b");
  if (!file) {
    printf("Error opening file: %s\n", fileName);
    return 0.0;  
  }

  Customer customer;
  int updated = 0;
  double totalSpendings = 0.0;

  while (fread(&customer, sizeof(Customer), 1, file)) {
    if (strcmp(customer.phoneNo, targetPhoneNo) == 0) {
      totalSpendings = customer.spendings;  // Get existing total spending
      customer.spendings += newSpendings;   // Update total spending
      fseek(file, -sizeof(Customer), SEEK_CUR);
      fwrite(&customer, sizeof(Customer), 1, file);

      updated = 1;
      break;
    }
  }

  fclose(file);

  if (!updated) {
    printf("Customer with phone number %s not found\n", targetPhoneNo);
  }

  return totalSpendings;  
}

void welcome();
double checkLoyalty();
int main() {
  welcome();
  char fileName[] = "customers.txt";
  char customerName[50];
  char customerPhoneNo[20];
  int numberOfItems;
  int numOfCustomer;

  printf("Enter current number of customers in line: \n");
  scanf("%d", &numOfCustomer);
  for (int i = 0; i < numOfCustomer; i++) {
    printf("Enter customer's name: ");
    scanf("%s", customerName);

    printf("Enter customer's phone number: ");
    scanf("%s", customerPhoneNo);

    printf("Enter number of items ordered: ");
    scanf("%d", &numberOfItems);
    int prices[] = {220, 180, 450};
    double totalPrice = 0;
    printf("Here is the Menu:\n 1.Sandwich\n 2.Burger\n 3.Pizza\n Now input the item codes \n:");
    for (int i = 0; i < numberOfItems; i++) {
      int x; scanf("%d", &x);
      x--; 
      totalPrice += prices[x];
    }

    Customer customer;
    FILE *file = fopen(fileName, "rb");
    double totalSpending = 0.0;
    if (file) {
      int found = 0;
      while (fread(&customer, sizeof(Customer), 1, file)) {
        if (strcmp(customer.phoneNo, customerPhoneNo) == 0) {
          found = 1;
          break;
        }
      }

      fclose(file);

      if (found) {
        totalSpending =
            updateCustomerSpendings(fileName, customerPhoneNo, totalPrice);
      } else {
        // Add new customer to the file
        customer.spendings = totalPrice;
        strcpy(customer.name, customerName);
        strcpy(customer.phoneNo, customerPhoneNo);

        file = fopen(fileName, "ab");
        if (file) {
          fwrite(&customer, sizeof(Customer), 1, file);
          fclose(file);
        } else {
          printf("Error opening file for writing: %s\n", fileName);
        }
      }
    } else {
      // Create new file
      file = fopen(fileName, "wb");
      if (file) {
        customer.spendings = totalPrice;
        strcpy(customer.name, customerName);
        strcpy(customer.phoneNo, customerPhoneNo);

        fwrite(&customer, sizeof(Customer), 1, file);
        fclose(file);
      } else {
        printf("Error creating file: %s\n", fileName);
      }
    }
    double percentage = checkLoyalty(totalSpending);
    push(percentage, totalPrice, customerName);
  }
  while (1) {
    char popped_name[20];
    double popped_data = pop(popped_name);

    if (popped_data != -1) {
        printf("Customer Served: Name: %s, Payable amount: %.2lf\n", popped_name, popped_data);
    } else break;

  }
  return 0;
}
void welcome() {
  const char *welcomeMessage = "Welcome to LoyaltyBites";
  printf("\n\n\t\t\t\t\t\t\t%s\n\n", welcomeMessage);
}