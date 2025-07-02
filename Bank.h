// Bank.h

#pragma once
#include<string>
#include<vector>
#include<map>


class Account
{
private:
	// Account Details
	std::string AName;
	int ANo;
	std::string APhNo;
	double ABalance;
	std::string APass;

	// pointer to the specific account
	Account* acc; 

public:
	// Default Constructor.
	Account(); 

	// parameterised constructor to create an 'Account' Object.
	Account* CAcc(std::string name, int acc_no, std::string ph_no, int deposit);

	// Display the account details.
	void ADetails();		
	// Return Account holder name.
	std::string GetAName();	
	// Return Account Number.
	int GetANo();	
	// Get & Set Password to an Account.
	void SetPass();						
	// true -> correct password, false -> incorrect password
	bool CheckPass(std::string pass);
	// Display Account Balance
	void CheckABalance();
	// Return Account Balance
	double GetABalance();
	// Take Money from the account.
	void Withdraw(int x);	
	// Put Money into the account.
	void Deposit(int x);				
};


class Bank
{
protected:
	// Bank Details
	std::string BName;
	std::string BIFSC;
	std::string BAddress;
public:
	// Default constructor of Bank.
	Bank() {};	
	// Map of Bank Name and it's details.
	Bank(std::map <std::string, std::string> B);	

private:
	// Pointer to all the Accounts in this bank.
	std::vector <Account*> AList;
	// Allocating new Account Numbers.
	int n;
	// Opening a New Account in this Bank.
	Account* CAcc();
	// Login to Your Account in this Bank.
	Account* Login();	
	// NetBanking Webpage
	void NetBanking(Account* acc);	
	// Returns Pointer to a Account
	Account* GetAcc(int x);			
	// Sending Money from the logined account.
	void SendMoney(Account *acc);		

public:
	// Return Bank's Name.
	std::string GetBName();
	// Return Bank's IFSC Code.
	std::string GetBIFSC();
	// Return Bank's Address.
	std::string GetBAddress();
	// Display Bank Details.
	void BDetails();
	// Display WebPage of this Bank.
	void WebPage();	
	// Recieve Money to an account in this bank with necessary transaction detials.
	bool ReceieveMoney(std::map<std::string, std::string> sender, std::map<std::string, std::string> receiver);
										
};

class Banks
{
private:
	// Pointer to the all the Bank Objects.
	static std::vector <Bank*> BList;	

public:
	// Creating Banks.
	static void LoadBanks();	
	// Return Bank Object.
	static Bank* GetBank(std::string BName);	
	// Acts as an Intermediatory to transfer money between two banks.
	static bool TransFerMoney(std::map<std::string, std::string> sender, std::map<std::string, std::string> receiver);
										
};


