#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Object
{
    std::map<std::string, std::string> Data;
public:
    // конструктор по умолчанию
    Object() = default;

    // деструктор
    ~Object() = default;

    // конструктор копирования
    Object(const Object&) = default;

    // оператор присваивания
    Object& operator=(const Object&) = default;

    // метод для изменения/добавления значения по ключу
    void Add(const std::string& key, const std::string& value)
    {
        Data[key] = value;
    }

    // метод для получения значения по ключу
    std::string GetByKey(const std::string& key) const
    {
        auto it = Data.find(key);
        if (it == Data.end())
           throw std::runtime_error("key not found");
        return it->second;
    }

    // метод для получения всех ключей в объекте
    std::set<std::string> Names() const
    {
        std::set<std::string> names;
        for (const auto& kv : Data)
        {
            names.insert(kv.first);
        }
        return names;
    }
    void clear()
    {
        Data.clear();
    }
};