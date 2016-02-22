Character::Character()
{
  hp = 100;
  exp = 0;
  level = 1;
  expToNextLevel = expBase = 10;
  money = 0;
  hand = new Equip();
  head = new Equip();
  body = new Equip();
  bottom = new Equip();
}

Character::~Character()
{
}

void Character::damage(int amount)
{
     hp -= amount;
}

void Character::useItem(int item)
{
     ivnent.use(item)
}

void Character::levelUp(int experience)
{
      expToNextLevel -= experience;
      if (expToNextLevel <= 0)
         level++
      getNewExp(expToNextLevel);
      expToNextLevel = expBase + expToNextLevel
      //baseHp += x;
         
}

void Character::increaseHP(int amount)
{
     //character.increaseHP(HealItem::use(Item::lookup(item))
     hp += amount;
}

void Character::getNewExp(int exp)
{
     baseExp *= 1.50;
}

void Character::incAtt(int i)
{
     att += hand.att*1;
}

void Character::incDef(int i)
{
     def += item.def*i;
}

void Character::equip(int index, int x)
{
     switch (x)
     {
            case 1:       hand.getIndex() = index; break;
            case 2;       head.getIndex() = index; break;
            case 3;       body.getIndex() = index; break;
            case 4;       bottom.getIndex() = index; break;
     }
}

void Character::unequip(int index)
{
     switch (x)
     {
            case 1:       hand.getIndex() = 0; break;
            case 2;       head.getIndex() = 0; break;
            case 3;       body.getIndex() = 0; break;
            case 4;       bottom.getIndex() = 0; break;
     }
}
