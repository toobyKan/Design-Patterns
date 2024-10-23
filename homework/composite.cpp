#include <iostream>
#include <vector>
#include <memory>

class ITeamSkills {
public:
    using ITeamSkillsPtr = std::shared_ptr<ITeamSkills>;
    virtual void Present() = 0;
    virtual void Defend() = 0;
};

class Employee : public ITeamSkills {
public:
    Employee(int id, const std::string& name):
        m_id(id), m_name(name)
    {}
    
    void Present() override {
        std::cout << "Employee.Present() id:" << m_id << ", Name: " << m_name << "\n";
    }
    
    void Defend() override {
        std::cout << "Employee.Defend() id:" << m_id << ", Name: " << m_name << "\n";
    }

private:
    int m_id;
    std::string m_name;
};

class Department : public ITeamSkills {
public:
    using DepartmentPtr = std::shared_ptr<Department>;
    
    Department(int id):
        m_id(id)
    {}
    
    void Present() override {
        std::cout << "Department.Present() id:" << m_id << "\n";
        for(const auto& member : m_members) {
            member->Present();
        }
    }
    
    void Defend() override {
        std::cout << "Department.Defend() id:" << m_id << "\n";
        for(const auto& member : m_members) {
            member->Defend();
        }
    }
    
    void AddToDepartment(const ITeamSkillsPtr& member) {
        m_members.push_back(member);
    }
    
private:
    int m_id;
    std::vector<ITeamSkillsPtr> m_members;
};

int main() {
    ITeamSkills::ITeamSkillsPtr emp1 = std::make_shared<Employee>(1, "Alice");
    ITeamSkills::ITeamSkillsPtr emp2 = std::make_shared<Employee>(2, "Bob"); 
    
    Department::DepartmentPtr dept1 = std::make_shared<Department>(101);
    dept1->AddToDepartment(emp1);
    
    Department::DepartmentPtr dept2 = std::make_shared<Department>(102);
    dept2->AddToDepartment(emp2);
    dept1->AddToDepartment(dept2);
    
    dept1->Present();
    dept1->Defend();
    
    return 0;
}
