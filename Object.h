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
    // ����������� �� ���������
    Object() = default;

    // ����������
    ~Object() = default;

    // ����������� �����������
    Object(const Object&) = default;

    // �������� ������������
    Object& operator=(const Object&) = default;

    // ����� ��� ���������/���������� �������� �� �����
    void Add(const std::string& key, const std::string& value)
    {
        Data[key] = value;
    }

    // ����� ��� ��������� �������� �� �����
    std::string GetByKey(const std::string& key) const
    {
        auto it = Data.find(key);
        if (it == Data.end())
           throw std::runtime_error("key not found");
        return it->second;
    }

    // ����� ��� ��������� ���� ������ � �������
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