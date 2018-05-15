#pragma once
#include "Object.h"

class Container
{
    std::map<std::string, Object> Data;

    enum class EAction
    {
        FindScheme,
        ReadFields,
        ReadObject,
        FindObject
    };
public:
    // конструктор по умолчанию
    Container() = default;

    // метод для получения объекта по названию;
    const Object& GetObject(const std::string& key) const
    {
        auto it = Data.find(key);
        if (it == Data.end())
            throw std::runtime_error("key not found");
        return it->second;
    }
    // метод для добавления нового объектa
    void AddObject(const std::string& key, const Object& obj)
    {
        if (key == "Scheme") // Scheme забронированно
            throw std::runtime_error("not valid key");

        if (Data.find(key) != Data.end()) // не должно быть такого ключа
            throw std::runtime_error("not valid key");


        // проверка на наличие всех полей у объкта
        /*
        if (!Data.empty())
        {
            auto names = obj.Names();
            auto exist = Data.cbegin()->second.Names();
            bool right = std::equal(names.begin(), names.end(), exist.begin());
            if (!right)
                throw std::runtime_error("not valid object");
        }
        */

        // добавляем
        Data[key] = obj;
    }

    // удаление по одному ключу
    void Erase(const std::string& key)
    {
        auto it = Data.find(key);
        if (it == Data.end())
            return;
        Data.erase(it);
    }
    // удаление по нескольким ключам
    void Erase(const std::set<std::string>& keys)
    {
        for (const auto& key : keys)
            Erase(key);
    }



    /////////////////////////////////////////////////////////////////////////////////
    /////////////////////////Если у каждого объекта все поля/////////////////////////
    /*
    // метод для сохранения объектов в файл в соответствующем формате
    void Save(const std::string& filename) const
    {
        std::ofstream ofs(filename);
        if (Data.empty())
        {
            ofs.close();
            return;
        }

        std::set<std::string> names = Data.begin()->second.Names();
        ofs << "#Scheme" << std::endl;
        for (const std::string& field : names)
        {
            ofs << "\"" << field << "\"" << std::endl;
        }
        for (const std::pair<std::string, Object>& object : Data)
        {
            ofs << "#" << object.first << std::endl;
            for (const auto& field : names)
            {
                ofs << "\"" << object.second.GetByKey(field) << "\"" << std::endl;
            }
        }
        ofs.close();
    }

    explicit Container(const std::string& filename)
    {
        EAction action = EAction::FindScheme;

        std::ifstream ifs(filename);

        std::string line;
        std::vector<std::string> schemes;
        std::string currentName;
        Object obj;
        size_t index = 0;
        while (std::getline(ifs, line))
        {
            if (action == EAction::FindScheme
                && line == "#Scheme")
            {
                action = EAction::ReadFields;
            }

            else if (EAction::ReadFields == action
                && !line.empty()
                && line[0] != '#')
            {
                size_t f = line.find_first_of('"', 1);
                if (f == std::string::npos)
                    throw std::runtime_error("wrong format");

                std::string value(line.begin() + 1, line.begin() + f);
                schemes.push_back(value);
            }

            else if (EAction::ReadFields == action
                && !line.empty()
                && line[0] == '#')
            {
                action = EAction::ReadObject;
                currentName.assign(line.begin() + 1, line.end());
            }

            else if (EAction::ReadObject == action
                && !line.empty()
                && line[0] != '#')
            {
                if (index == schemes.size())
                    throw std::runtime_error("wrong format");

                size_t f = line.find_first_of('"', 1);
                if (f == std::string::npos)
                    throw std::runtime_error("wrong format");

                std::string value(line.begin() + 1, line.begin() + f);
                obj.Add(schemes[index], value);
                ++index;
            }

            else if (EAction::ReadObject == action
                && !line.empty()
                && line[0] == '#')
            {
                if (index != schemes.size())
                    throw std::runtime_error("wrong format");

                AddObject(currentName, obj);
                index = 0;
                currentName.assign(line.begin() + 1, line.end());
            }
        }

        if (EAction::ReadObject == action)
        {
            if (index != schemes.size())
                throw std::runtime_error("wrong format");
            AddObject(currentName, obj);
        }
    }
    */
    /////////////////////////////////////////////////////////////////////////////////
    /////////////////////////Если у объекта отсутствует какое- либо поле/////////////
    // метод для сохранения объектов в файл в соответствующем формате
    void Save(const std::string& filename) const
    {
        std::ofstream ofs(filename);
        if (Data.empty())
        {
            ofs.close();
            return;
        }
        ofs << "#Scheme" << std::endl;

        for (const std::pair<std::string, Object>& object : Data)
        {
            ofs << "#" << object.first << std::endl;
            auto names = object.second.Names();
            for (const auto& field : names)
            {
                ofs << field << '=' << object.second.GetByKey(field) << std::endl;
            }
        }
        ofs.close();
    }

    explicit Container(const std::string& filename)
    {
        std::ifstream ifs(filename);
        std::string line;
        //std::vector<std::string> schemes;
        std::string currentName;
        Object obj;

        std::string Key;
        std::string Value;

        EAction action = EAction::FindScheme;

        while (std::getline(ifs, line))
        {
            if (action == EAction::FindScheme
                && line == "#Scheme")
            {
                action = EAction::FindObject;
            }

            else if (EAction::FindObject == action
                && !line.empty()
                && line[0] == '#')
            {
                //запись Ninja1  // #Ninja1 <--- 
                currentName.assign(line.begin() + 1, line.end());
                action = EAction::ReadObject;
            }

            else if (EAction::ReadObject == action
                && !line.empty()
                && line[0] != '#')
            {
                // считываем до равно Key, после Value // Colour=Blue <---    
                auto it = line.find('=');
                Key.assign(line.begin(), line.begin() + it);
                Value.assign(line.begin() + it + 1, line.end());
                obj.Add(Key, Value);
            }

            else if (EAction::ReadObject == action
                && !line.empty()
                && line[0] == '#')
            {
                AddObject(currentName, obj); // вставляем прошлый Объект
                obj.clear();
                currentName.assign(line.begin() + 1, line.end()); // #Ninja2 <---
            }
        }

        if (EAction::ReadObject == action)
        {
            AddObject(currentName, obj);
        }
    }
};