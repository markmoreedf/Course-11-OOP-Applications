#pragma once
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsUtility.h"

class clsCurrency
{
private:

    // currencies data written in the file as follows:
    // countryName _Delimiter currencyCode _Delimiter currencyName _Delimiter rate

    inline static const std::string _CurrenciesDataFileName = "data/Currencies.txt";
    inline static const std::string _Delimiter = "#//#";

    enum enMode { EmptyMode = 0, UpdateMode = 1};
    enMode _Mode;
    std::string _countryName;
    std::string _crCode;
    std::string _crName;
    double _rate;

    static clsCurrency _ConvertLineToCurrencyObject(const string& dataLine)
    {
        vector <string> vCurrencyData = clsString::Split(dataLine, _Delimiter);

        // Expected Data Members Count = 4
        if (vCurrencyData.size() != 4)
            return _GetEmptyCurrencyObj();

        return clsCurrency(enMode::UpdateMode,
            vCurrencyData[0],
            vCurrencyData[1],
            vCurrencyData[2],
            stod(vCurrencyData[3]));
    }
    static string _ConvertCurrencyObjectToLine(const clsCurrency& currency)
    {
        string lineOfData = "";
        lineOfData += currency.countryName + _Delimiter;
        lineOfData += currency.crCode + _Delimiter;
        lineOfData += currency.crName + _Delimiter;
        lineOfData += to_string(currency.rate) + _Delimiter;

        return lineOfData;
    }
    static clsCurrency _GetEmptyCurrencyObj()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }
    static vector<clsCurrency> _LoadCurrencyFileToVecObjects()
    {
        vector<string> dataLines = clsUtility::LoadFileDataToVecString(_CurrenciesDataFileName, _Delimiter, 4);

        vector<clsCurrency> vCurrencies;

        for (const string& line : dataLines) {
            vCurrencies.push_back(_ConvertLineToCurrencyObject(line));
        }
        return vCurrencies;
    }
    static void _SaveVecCurrenciesToFile(const vector<clsCurrency>& vCurrencies, bool appendMode)
    {
        ofstream dataFile;
        if (appendMode)
            dataFile.open(_CurrenciesDataFileName, ios::out | ios::app); // keep the old data and append new data
        else
            dataFile.open(_CurrenciesDataFileName, ios::trunc); // overwrite the file
        if (dataFile.is_open())
        {
           for (const clsCurrency& currency : vCurrencies) {

                dataFile << _ConvertCurrencyObjectToLine(currency) << endl;
            }
            dataFile.close();

        }
    }

    bool _Update() const
    {
        vector<clsCurrency> vCurrencies = _LoadCurrencyFileToVecObjects();

        for (clsCurrency& currency : vCurrencies) {
            if (currency.crCode == this->_crCode) {
                currency = *this;
                _SaveVecCurrenciesToFile(vCurrencies, false);
                return true;
            }
        }
        return false;
    }

public:
    std::string GetCountryName() const { return _countryName; }
    __declspec(property(get = GetCountryName)) std::string countryName;   // read only property. no setter function. 
   
    std::string GetCurrencyCode() const { return _crCode; }
    __declspec(property(get = GetCurrencyCode)) std::string crCode;   // read only property. no setter function. 

    std::string GetCurrencyName() const { return _crName; }
    __declspec(property(get = GetCurrencyName)) std::string crName;   // read only property. no setter function. 

    double GetRate() const { return _rate; }
    __declspec(property(get = GetRate)) double rate;   // read only property. setter function will be implemented in strict conditions. 

    clsCurrency(enMode mode, std::string countryName, std::string currencyCode, std::string currencyName, double rate)
    {
        this->_Mode = mode;
        this->_countryName = countryName;
        this->_crCode = currencyCode;
        this->_crName = currencyName;
        this->_rate = rate;
    }

    bool IsEmpty() const { return _Mode == enMode::EmptyMode; }

    static bool IsCurrencyExist(const string& currencyName)
    {
        clsCurrency currency = clsCurrency::FindCurrencyByName(currencyName);
        return (!currency.IsEmpty());
    }

    static clsCurrency FindCurrencyByCode(const string& currencyCode)
    {
        vector<clsCurrency> vCurrencies = _LoadCurrencyFileToVecObjects();
        for (const clsCurrency& currency : vCurrencies) {
            if (clsString::UpperAllString(currency.crCode) == clsString::UpperAllString(currencyCode))
                return currency;
        }
        return _GetEmptyCurrencyObj();

    }
    static clsCurrency FindCurrencyByName(const string& currencyName)
    {
        vector<clsCurrency> vCurrencies = _LoadCurrencyFileToVecObjects();
        for (const clsCurrency& currency : vCurrencies) {
            if (clsString::UpperAllString(currency.crName) == clsString::UpperAllString(currencyName))
                return currency;
        }
        return _GetEmptyCurrencyObj();
    }
    static clsCurrency FindCurrencyByCountry(const string & countryName)
    {
        vector<clsCurrency> vCurrencies = _LoadCurrencyFileToVecObjects();
        for (const clsCurrency& currency : vCurrencies) {
            if (clsString::UpperAllString(currency.countryName) == clsString::UpperAllString(countryName))
                return currency;
        }
        return _GetEmptyCurrencyObj();
    }


    static void SetRate(const string& currencyCode, double newRate)
    {
        if (newRate <= 0)
        { return; }

        clsCurrency currency = clsCurrency::FindCurrencyByCode(currencyCode);

        if (currency.IsEmpty())
        { return; }

        currency._rate = newRate;
        currency._Update();
    }
    static void SetRate(clsCurrency & currency,double newRate)
    {
        if (newRate <= 0)
        { return; }

        if (currency.IsEmpty())
        { return; }

        currency._rate = newRate;
        currency._Update();
    }
    void SetRate(double newRate)
    {
        SetRate(*this, newRate);
    }

    static vector<clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencyFileToVecObjects();
    }

};

