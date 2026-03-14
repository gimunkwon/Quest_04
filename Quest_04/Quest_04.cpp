#include <iostream>
#include <vector>
#include <string>

using list = std::pair<std::string,std::vector<std::string>>;

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe 
{
public:
    //Getter
    _forceinline  std::string GetPotionName() const{ return potionName; }
    _forceinline  std::vector<std::string> getIngredients() const{ return ingredients; }
    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {}
    
private:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경
};


// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop 
{
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) 
    {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const 
    {
        if (recipes.empty()) 
        {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) 
        {
            std::cout << "- 물약 이름: " << recipes[i].GetPotionName() << std::endl;
            std::cout << "  > 필요 재료: ";
            
            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].getIngredients().size(); ++j) 
            {
                std::cout << recipes[i].getIngredients()[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].getIngredients().size() - 1) 
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }
    
    // 물약이름 or 재료로 등록되있는 물약찾는 메서드
    bool findRecipe(const std::string& name, const std::string& ingredient = "")
    {
        bool bIsNameFound = false;
        bool bIsIngredientFound = false;
        std::string findingname = name;
        std::string findingingredient = ingredient;
        std::vector<list> v_tmpPotion(recipes.size());
        
        // 물약의 이름으로 찾기
        if (name != "")
        {
            for (const auto& recipe : recipes)
            {
                if (findingname == recipe.GetPotionName())
                {
                    bIsNameFound = true;
                }
            }
        }
        // 물약의 이름으로도 찾지 못했을 경우
        else if (!bIsIngredientFound)
        {
            for (int i = 0; i < recipes.size(); ++i)
            {
                for (int j = 0; j < recipes[i].getIngredients().size(); ++j)
                {
                    if(recipes[i].getIngredients()[j] == findingingredient)
                    {
                        bIsIngredientFound = true;
                        v_tmpPotion[i].first = recipes[i].GetPotionName();
                        v_tmpPotion[i].second = recipes[i].getIngredients();
                    }
                }
                
            }
        }
        
        if (bIsNameFound)
        {
            std::cout << findingname << "을 찾았습니다. 레시피를 출력합니다." << "\n";
            for (int i = 0; i < recipes.size(); ++i)
            {
                if (recipes[i].GetPotionName() == findingname)
                {
                    for (int j = 0; j < recipes[i].getIngredients().size(); ++j)
                    {
                        std::cout << recipes[i].getIngredients()[j] << "\n";
                        
                    }
                    break;
                }
            }
        }
        else if (bIsIngredientFound)
        {
            std::cout << "재료와 일치하는 레시피를 출력합니다." << "\n";
            
            for (int i = 0; i < v_tmpPotion.size(); i++)
            {
                std::cout << v_tmpPotion[i].first <<"\n";
                
                for (int j = 0; j < v_tmpPotion[i].second.size(); j++)
                {
                    std::cout << v_tmpPotion[i].second[j] << "\n";
                }
            }
    
        }
        else
        {
            std::cout << findingname << "을 찾을수 없습니다!" << "\n";
            return false;
        }
    }
};

int main() 
{
    AlchemyWorkshop myWorkshop;
    
    while (true) {
        std::cout << "⚗️ 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 검색" << std::endl;
        std::cout << "4. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        
        // switch case문으로 수정
        switch (choice)
        {
        case 1:
            {
                if (choice == 1)
                {
                    std::string name;
                    std::cout << "물약 이름: ";
                    std::cin.ignore(10000, '\n');
                    std::getline(std::cin, name);

                    // 여러 재료를 입력받기 위한 로직
                    std::vector<std::string> ingredients_input;
                    std::string ingredient;
                    std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;
            
                    while (true) {
                        std::cout << "재료 입력: ";
                        std::getline(std::cin, ingredient);
                
                        // 사용자가 '끝'을 입력하면 재료 입력 종료
                        if (ingredient == "끝") {
                            break;
                        }
                        ingredients_input.push_back(ingredient);
                    }

                    // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
                    if (!ingredients_input.empty()) {
                        myWorkshop.addRecipe(name, ingredients_input);
                    } else {
                        std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
                    }
                }    
            }
            break;
            
        case 2:
            myWorkshop.displayAllRecipes();
            break;
        case 3:
            {
                std::string inputname;
                std::cout << "이름을 입력해주세요" <<"\n";
                std::cin.ignore(10000, '\n');
                std::getline(std::cin, inputname);
                if (myWorkshop.findRecipe(inputname))
                {
                    break;
                }
                else
                {
                    std::string ingredient;
                    std::cout << "재료를 입력해주세요" << "\n";
                    std::getline(std::cin, ingredient);
                    myWorkshop.findRecipe("",ingredient);
                }
            }
            break;
        case 4:
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;
        }
    }

    return 0;
}