#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
  return abs(x - y);
}

class Creature
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
protected:
  const string nom_;
  int niveau_;
  int points_de_vie_;
  int force_;
  int position_;
public:
  Creature() = default;
  Creature(string, int, int, int, int);
  bool vivant() const;
  int points_attaque() const;
  void deplacer(int);
  void adieux() const;
  void faiblir(int);
  void afficher() const;
  int position() const;
};

Creature::Creature(string nombre, int nivel, int salud, int fuerza, int pos = 0)
: nom_(nombre), niveau_(nivel), points_de_vie_(salud), force_(fuerza), position_(pos) {}

bool Creature::vivant() const {
  if (points_de_vie_ > 0) return true;
  else return false;
}

int Creature::points_attaque() const {
  if (vivant()) return niveau_ * force_;
  else return 0;
}

void Creature::deplacer(int add) {
  if (vivant()) position_ += add;
}

void Creature::adieux() const {
  cout << nom_ << " n'est plus !" << endl;
}

void Creature::faiblir(int danio) {
  points_de_vie_ -= danio;
  if (points_de_vie_ <= 0) {
    points_de_vie_ = 0;
    adieux();
  }
}

void Creature::afficher() const {
  cout << nom_ << ", niveau: " << niveau_
  << ", points de vie: " << points_de_vie_
  << ", force: " << force_
  << ", points d'attaque: " << points_attaque()
  << ", position: " << position_ << endl;
}

int Creature::position() const {
  return position_;
}

class Dragon : public Creature {
protected:
  int portee_flamme_;
public:
  Dragon(string, int, int, int, int, int);
  void voler(int);
  void souffle_sur(Creature&);
};

Dragon::Dragon(string nombre, int nivel, int salud, int fuerza, int rango, int pos = 0)
: Creature(nombre, nivel, salud, fuerza, pos), portee_flamme_(rango) {}

void Dragon::voler(int pos) {
  if (vivant()) position_ = pos;
}

void Dragon::souffle_sur(Creature& otro) {
  if (vivant() and otro.vivant()) {
    int d = distance(position_, otro.position());
    // si esta en el rango de su flama
    if (d <= portee_flamme_) {
      otro.faiblir(points_attaque());
      faiblir(d);
    }
    // luego de la batalla
    if (vivant() and not otro.vivant()) {
      niveau_++;
    }
  }
}

class Hydre : public Creature {
protected:
  int longueur_cou_;
  int dose_poison_;
public:
  Hydre(string, int, int, int, int, int, int);
  void empoisonne(Creature&);
};

Hydre::Hydre(string nombre, int nivel, int salud, int fuerza, int cuello, int veneno, int pos = 0)
: Creature(nombre, nivel, salud, fuerza, pos), longueur_cou_(cuello), dose_poison_(veneno) {}

void Hydre::empoisonne(Creature& otro) {
  if (vivant() and otro.vivant()) {
    int d = distance(position_, otro.position());
    if (d <= longueur_cou_) {
      int danio = points_attaque() + dose_poison_;
      otro.faiblir(danio);
    }
    if (not otro.vivant()) {
      niveau_++;
    }
  }
}

void combat(Dragon& dragon, Hydre& hydra) {
  hydra.empoisonne(dragon);
  dragon.souffle_sur(hydra);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  Dragon dragon("Dragon rouge"   , 2, 10, 3, 20         );
  Hydre  hydre ("Hydre maléfique", 2, 10, 1, 10, 1,  42 );

  dragon.afficher();
  cout << "se prépare au combat avec :" << endl;
  hydre.afficher();

  cout << endl;
  cout << "1er combat :" << endl;
  cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
       << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon vole à proximité de l'hydre :" << endl;
  dragon.voler(hydre.position() - 1);
  dragon.afficher();

  cout << endl;
  cout << "L'hydre recule d'un pas :" << endl;
  hydre.deplacer(1);
  hydre.afficher();

  cout << endl;
  cout << "2e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon avance d'un pas :" << endl;
  dragon.deplacer(1);
  dragon.afficher();

  cout << endl;
  cout << "3e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "4e Combat :" << endl;
  cout << "    quand une créature est vaincue, rien ne se passe." << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  return 0;
}
