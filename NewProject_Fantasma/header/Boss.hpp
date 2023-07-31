#ifndef BOSS_HPP
#define BOSS_HPP
#include "Bandit.hpp"
#include <string>
using namespace std;

class Boss : public Bandit {
    private:
        std::string bossName;
        double selfHealAbility;
    public:
        Boss(double bh, double ba, std::string bn, double sh, int TextureX, int TextureY) : Bandit(bh, ba, TextureX,TextureY, sf::Vector2u(512,512)), bossName(bn), selfHealAbility(sh) {}
        void selfHeal();
        std::string getBossName();
};

#endif //BOSS_HPP