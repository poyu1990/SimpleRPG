class HealItem : public Item
{
      HealItem();
      ~HealItem(();
      
      int use(int i);
      int lookup(string s);     
      
      private:
      int amount[32];
      
}
