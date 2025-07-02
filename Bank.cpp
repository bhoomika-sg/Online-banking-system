// Bank.cpp

#include<iostream>
#include<iomanip>
#include<Windows.h>
#include "Bank.h"
#include "Bank.h"


// // Account Class Methods.
Account::Account()
{
	acc = this;
}

Account* Account::CAcc(std::string name, int acc_no, std::string ph_no, int deposit)
{
	acc->AName = name;
	acc->ANo = acc_no;
	acc->APhNo = ph_no;
	acc->ABalance = deposit;
	acc->SetPass();

	return acc;
}

std::string Account::GetAName()
{
	return AName;
}


int Account::GetANo()
{
	return ANo;
}

void Account::ADetails()
{
	std::cout << "--------------------------------------------\n";
	std::cout << "ACCOUNT DETAILS	: \n";
	std::cout << "A/C Holder		: " << AName << "\n";
	std::cout << "A/C No			: " << ANo << "\n";
	std::cout << "Phone No		: " << APhNo << "\n";
	std::cout << "--------------------------------------------\n";
}

void Account::SetPass()
{
	std::string pass;
	std::cout << "Set Your PassWord		: ";
	
	// Make sure that Password is not Visible while entering.
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	std::cin >> pass;
	// Cleanup
	SetConsoleMode(hStdin, mode);
	std::cout << "\n";

	// Storing Password in Account Object;
	APass = pass;
}

bool Account::CheckPass(std::string pass)
{
	return APass == pass;
}

void Account::CheckABalance()
{
	std::cout << "Account Balance : " << ABalance<< "\n";
}

double Account::GetABalance()
{
	return ABalance;
}

void Account::Withdraw(int x=0)
{
	if (x == 0)
	{
		std::cout << "Enter the Amount to WithDraw : ";
		std::cin >> x;
	}

	if (x > ABalance)
	{
		std::cout << "INSUFFICIENT BALANCE\n";
		return;
	}

	ABalance -= x;
	//std::cout << x << " Rs has been withdrawed\n";
	return;
}

void Account::Deposit(int x=0)
{
	if (x == 0)
	{
		std::cout << "Enter the Amount to Deposit : \n";
		std::cin >> x;
	}

	ABalance += x;
	//std::cout << x << " Rs has been Deposited\n";
	return;
}


// // Bank Class Methods.

Bank::Bank(std::map <std::string, std::string> B)
{
	//std::cout << "Creating " << B["BName"] << " Bank \n";
	this->BName = B["BName"];
	this->BIFSC = B["BIFSC"];
	this->BAddress = B["BAddress"];
	n = 1;
}

void Bank::BDetails()
{
	std::cout << "--------------------------------------------\n";
	std::cout << "BANK DETAILS......: \n";
	std::cout << "Bank Name		:" << BName << "\n";
	std::cout << "Bank IFSC		:" << BIFSC << "\n";
	std::cout << "Bank Address		:" << BAddress << "\n";
	std::cout << "--------------------------------------------\n";
}

Account* Bank::CAcc()
{
	// Creating a New Account in this Bank.


	// Getting Necessary Details from the user to Create a New Bank Account.
	std::string name, ph_no;
	int deposit;
	std::cout << "ACCOUNT OPENING \n";

	std::cout << "Enter your Name			: ";
	std::cin >> name;

	std::cout << "Enter your Phone Number		: ";
	std::cin >> ph_no;

	std::cout << "Intital deposit			: ";
	std::cin >> deposit;

	// New Account Object
	Account* acc = new Account;
	acc = acc->CAcc(name, n, ph_no, deposit);

	// Storing New Account Object in the Accounts list of this bank.
	AList.push_back(acc);	


	std::cout << "========================================================\n";
	std::cout << "Congrats... Your Account is Successfully Created\n";
	std::cout << "========================================================\n";

	std::cout << "PASSBOOK......: \n";
	BDetails();
	acc->ADetails();
	std::cout << "Use NET BANKING For Faster Banking Services \n";
	std::cout << "========================================================\n";
	n++;
	return acc;
}

std::string Bank::GetBName()
{
	return BName;
}

std::string Bank::GetBIFSC()
{
	return BIFSC;
}

std::string Bank::GetBAddress()
{
	return BAddress;
}

Account* Bank::GetAcc(int x)
{
	for (auto a : AList)
	{
		// Checking for valid Account Number.
		if (a->GetANo() == x)		
			return a;
	}

	std::cout << "Invalid Account Number \n";
	return NULL;
}

Account* Bank::Login()
{
	// Loging in to user's NetBanking portal

	// Get Account No.
	std::cout << "-=--=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=\n";
	int acc_no{};
	std::cout <<BName<<".com\n"<< "NET BANKING PORTAL\n";
	std::cout << "Login...\n";
	std::cout << "Enter your user id / Acc No : ";
	std::cin >> acc_no;

	// Search for that account;
	Account* acc = GetAcc(acc_no);

	// Account does not exist!
	if (!acc)
	{
		std::cout << "InValid Account Number \n";
		std::cout << "Login Failed \n";
		return acc;
	}

	// Hiding Password while typing.

	std::string pass{};
	std::cout << "Enter Your PassWord : ";
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	std::cin >> pass;
	// Set Console MOde to NOrmal
	SetConsoleMode(hStdin, mode);
	std::cout << "\n";

	// Checking Password
	if (!(acc->CheckPass(pass)))
	{
		std::cout << "InValid PassWord \n";
		std::cout << "LogIn Un-SuccessFul \n";
		return NULL;
	}

	std::cout << "LogIn SuccessFul \n";
	std::cout << "-=--=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=\n";

	return acc;
}

void Bank::SendMoney(Account *acc)
{
	// Transfering Money to another account using NetBanking.


	int amt{}, RANo{};
	std::string RBName;
	bool valid = true;

	std::cout << "-----------------------------------------------------\n";
	std::cout << "Money TransFer\n";
	// Get Transfer amount.
	std::cout << "Enter the amount to send	: ";
	std::cin >> amt;
	// Check for sufficient balance to transer the money.

	// Amount to transfer is greater than the available balance.
	if (amt > acc->GetABalance())
	{
		std::cout << "InSufficient Balance...\n";
		std::cout << "Retry with Lower Amount...\n";
		valid = false;;
	}
	if (!valid)
		return;

	// Get Receiver's Bank name and Accont Number.
	int choice{};
	std::cout << "Choose Receiver Bank \n";
	std::cout << "1. ICICI \n";
	std::cout << "2. HDFC \n";
	std::cout << "Enter Your Choice		: ";
	std::cin >> choice;

	switch (choice)
	{
	case 1: RBName = "ICICI"; break;
	case 2: RBName = "HDFC"; break;
	default: std::cout << "InValid Choice \n"; valid = false;
	}
	if (!valid)
		return;

	std::cout << "Enter Receiver's Account Number : ";
	std::cin >>RANo;

	std::map<std::string, std::string> sender;
	std::map<std::string, std::string> receiver;

	// Sender Details;
	sender["BName"] = BName;
	sender["AName"] = acc->GetAName();
	sender["ANo"] = std::to_string(acc->GetANo());
	sender["Amount"] = std::to_string(amt);

	//Receiver Details;
	receiver["BName"] = RBName;
	receiver["ANo"] = std::to_string(RANo);
	
	acc->Withdraw(amt);\

	// Passing the necessary 'Sender' and 'Receiver' details to
	//  intermediatory 'TranFerMoney' function to facitilate the transaction.
	bool status = Banks::TransFerMoney(sender, receiver);	
	if (!status)
	{
		std::cout << "Transfer Failed !!\n";
		acc->Deposit(amt);
		std::cout << "-----------------------------------------------------\n";
		return;
	}

	std::cout << "Transfer SuccessFull !!\n";
	std::cout << "-----------------------------------------------------\n";

	return;
}

bool Bank::ReceieveMoney(std::map<std::string, std::string> sender, std::map<std::string, std::string> receiver)
{
	// Recieving Money to an account.
	

	//Check Account;
	int RANo = std::stoi(receiver["ANo"]);
	Account* racc = GetAcc(RANo);
	if (!racc)
	{
		std::cout << "Receiver Bank Account Does Not Exist \n";
		return false;
	}

	//Deposit in Receiver's account;
	int amt = std::stoi(sender["Amount"]);
	racc->Deposit(amt);
	return true;
}


void Bank::NetBanking(Account* acc = nullptr)
{
	// Login Account;
	if (!acc)
	{ 
		acc = this->Login();
	}

	// Login Failed ;
	if (!acc)
	{
		return;
	}

	// Chosing the service.
	int choice{};
	while (choice != 6)
	{
		std::cout << GetBName() << ".com\n";
		std::cout << "Welcome " << acc->GetAName() << "! \n";
		std::cout << "================================================\n";
		std::cout << "Choose Your Service : \n";
		std::cout << "1. Check Balance \n";
		std::cout << "2. WithDraw  \n";
		std::cout << "3. Deposit \n";
		std::cout << "4. Account Details \n";
		std::cout << "5. Send Money \n";
		std::cout << "6. Logout \n";
		std::cout << "Enter Your Service Choice : ";
		std::cin >> choice;
		std::cout << "================================================\n";

		switch (choice)
		{
		case 1: acc->CheckABalance(); break;
		case 2: acc->Withdraw(); break;
		case 3: acc->Deposit(); break;
		case 4: BDetails(); acc->ADetails(); break;
		case 5: SendMoney(acc); break;
		case 6: std::cout << "Thank You \n"; break;
		default: std::cout << "Invalid Choice \n";
		}
	}
}

void Bank::WebPage()
{
	// WebPage of a Bank.


	int choice{};
	while (choice != 3)
	{
		std::cout << "================================================\n";
		std::cout << "||                                            ||\n";
		std::cout << "||    Welcome to " << std::setw(30) << std::left << BName <<"\n";
		std::cout << "||                                            ||\n";
		std::cout << "================================================\n";
		std::cout << "||                                            ||\n";
		std::cout << "||    Choose Your Service :                   ||\n";
		std::cout << "||    1. Create Account                       ||\n";
		std::cout << "||    2. Net Banking                          ||\n";
		std::cout << "||    3. Go Back                              ||\n";
		std::cout << "||                                            ||\n";
		std::cout << "||    Enter Your Service Choice : ";
		std::cin >> choice;
		std::cout << "||                                            ||\n";
		std::cout << "================================================\n";

		switch (choice)
		{
		case 1:	CAcc(); break;
		case 2:	NetBanking(); break;
		case 3: break;
		default: std::cout << "InValid Choice \n";
		}	
		std::cout << "================================================\n";
	}
}



// // Banks Class Methods.

std::vector<Bank*> Banks::BList;		// Global List of all the banks objects.

void Banks::LoadBanks()
{
	// Create's All the Bank Objects and stores it into the list of banks.

	// Loading ICICI Bank with necessary details.
	std::map <std::string, std::string> BDetails;
	BDetails["BName"] = "ICICI";
	BDetails["BIFSC"] = "ICICDVG001";
	BDetails["BAddress"] = "Davangere";
	Bank* newBank = new Bank{ BDetails };
	BList.push_back(newBank);

	// Loading HDFC Bank with necessary details.
	BDetails["BName"] = "HDFC";
	BDetails["BIFSC"] = "HDFCMYS002";
	BDetails["BAddress"] = "Mysore";
	newBank = new Bank{ BDetails };
	BList.push_back(newBank);
}

Bank* Banks::GetBank(std::string BName)
{
	for (auto b : BList)
	{
		// Add Case Insensitivity;
		if (b->GetBName() == BName)
			return b;
	}

	return NULL;
}

bool Banks::TransFerMoney(std::map<std::string, std::string> sender, std::map<std::string, std::string> receiver)
{
	Bank* bank = GetBank(receiver["BName"]);

	// InValid Bank
	if (!bank)
	{
		std::cout << "Bank Does Not Exist \n";
		return false;
	}

	// Sending necessary details to bank to recieve the money.
	return bank->ReceieveMoney(sender, receiver);

}


