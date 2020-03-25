#include "JSON.h"

JSON::JSON(std::string& _key, std::string& _value) :
	key{ _key }, value{ _value } {
	
}

JSON::JSON(std::string& _key, std::list<std::string>& _values) :
	key{ _key }, values{ _values } {

}

JSON::~JSON() {
	this->key.clear();
	this->value.clear();
	this->values.clear();
}

void JSON::setValue(std::string& value) {
	this->value = value;
}

void JSON::setValues(std::list<std::string>& values) {
	this->values = values;
}

void JSON::setValues(std::string& value) {
	this->values.push_back(value);
}

void JSON::setKey(std::string& key) {
	this->key = key;
}

std::string JSON::getKey() {
	return this->key;
}

std::string JSON::getValue() {
	return this->value;
}

std::list<std::string> JSON::getValues() {
	return this->values;
}

/*
	ogarn�� architekture projektu

	statyczna metoda kr�tka zwraca wska�nik na object

	klasa kt�ra przechowuje dane JSON

	metoda kt�ra zwraca w ka�dym momencie itp

	zagnie�d�enie warto�ci

	konwersja warto�ci
*/