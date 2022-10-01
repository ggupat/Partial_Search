#include <stdio.h>
#include <string.h>
 
void Divide_Search_String(const char* search, char* first, char* second) //function that divide string based on '*'
{
	int count = 0; //variable for check whether there is '*' or isn't
	for (int t = 0; t < strlen(search); t++) //Out loop for find '*'
	{
		if (*(search + t) == '*')
		{
			count++; //there is '*' so ++;
			for (int i = 0; i < t; i++)
			{
				*(first + i) = *(search + i);
				if (i == t - 1)
				{
					*(first + i + 1) = NULL; //make the end of string
				}
			}
			for (int j = t; j < strlen(search); j++)
			{
				*(second + (j - t)) = *(search + j + 1);
				if (j == strlen(search) - 1)
				{
					*(second + j + 1) = NULL;
				}
			}
		}
	}
	if (count == 0) //there isn't '*'
	{
		for (int i = 0; i < strlen(search); i++)
		{
			*(first + i) = *(search + i);
			if (i == strlen(search) - 1)
			{
				*(first + i + 1) = NULL;
			}
		}
		*second = NULL;
	}
}
int Partial_Match_Count(const char* string, const char* first, const char* second) //function that do partial match
{
	int count = 0; //variable for return (how many partial match)
	int breaker = 0; //variable for escape loop so that avoid overlap loop
	for (int t = 0; t < strlen(string); t++) //Loop for check the first string with string
	{
		breaker = 0; //reset breaker
		if (*(string + t) == *first)
		{
			for (int p = 0; p < strlen(first); p++)
			{
				if (breaker == 1)
				{
					break; //it means already checked, so break loop
				}
				if (*(string + t + p) == *(first + p))
				{
					if (p == strlen(first) - 1) //Exact match between string and first is succeed.
					{
						for (int i = 1; i < strlen(string) - t - p; i++) //Loop for check the second string with string
						{
							if (breaker == 1)
							{
								break;
							}
							if (*(string + t + p + i) == *first) //Have to break loop to avoid overlap
							{
								break;
							}
							else if (*(string + t + p + i) == *second)
							{
								for (int j = 0; j < strlen(second); j++)
								{
									if (*(string + t + p + i + j) == *(second + j))
									{
										if (j == strlen(second) - 1) //Exact match between string and second is succeed
										{
											count++;
											breaker = 1; //breaker++ to return to first out loop
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return count;
}
#define NUM_TEST_SET 7
int main()
{
	char test_str[NUM_TEST_SET][256] = { "hello mister monkey", "hello mister monkey", "hello mister monkey", "My name is lee jongho",
	"my name is lee jongho", "My name is hong gil dong, My brother is hong je dong. My sister is hong gilja, and her friend is hongdong",
	"A thief named hong gil dong lived with friends named hong gil don and hong gil ja and hhhong gil dong and kong gil dong and honggil dong and hong gil donggg in a village named hong gil dong village." };
	char test_search_str[NUM_TEST_SET][128] = { "money", "mon*ey", "m*y", "lee *ho", "lee *ha", "hong*dong", "hong *dong" };
 
	for (int i = 0; i < NUM_TEST_SET; i++) //loop for check all test set
	{
		char* str = test_str[i];
		char* search_str = test_search_str[i];
 
		char first[128];
		char second[128];
		Divide_Search_String(search_str, first, second); //call function by reference / divide the string
 
		printf("\n//--- Experiment (%d) ---\n", i + 1); //print output
		printf("[String:] %s\n", str);
		printf("[Search-First:] [%s]\n", first);
		printf("[Search-Second:] [%s]\n", second);
 
		int num_matches = Partial_Match_Count(str, first, second); //call function by reference / do partial match
		printf("[Num Matches:] %d\n", num_matches);
	}
 
	return 0;
}