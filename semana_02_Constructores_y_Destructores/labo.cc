#include <iostream>
#include <string>
using namespace std;

class Souris
{
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
private:
double poids;
string couleur;
int age, esperance_vie;
bool clonee;

public:
Souris() = default;

Souris(double weight, string color, int edad = 0, int life = 36)
: poids(weight), couleur(color), age(edad), esperance_vie(life), clonee(false) {
  cout << "Une nouvelle souris !" << endl;
}

Souris(Souris const& otro)
: poids(otro.poids), couleur(otro.couleur), age(otro.age), clonee(true) {
  esperance_vie = 4 * otro.esperance_vie / 5;
  cout << "Clonage d'une souris !" << endl;
}

~Souris() { cout << "Fin d'une souris..." << endl; }

void afficher() {
  cout << "Une souris " << couleur;
  if (clonee) cout << ", clonee,";
  cout << " de " << age << " mois et pesant " << poids << " grammes"<< endl;
}

void vieillir() {
  age++;
  if (clonee and 2 * age > esperance_vie) couleur = "verte";
}

void evolue() {
  while (age < esperance_vie) vieillir();
}
  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

}; // fin de la classe Souris

int main()
{
  Souris s1(50.0, "blanche", 2);
  Souris s2(45.0, "grise");
  Souris s3(s2);
  // ... un tableau peut-être...
  s1.afficher();
  s2.afficher();
  s3.afficher();
  s1.evolue();
  s2.evolue();
  s3.evolue();
  s1.afficher();
  s2.afficher();
  s3.afficher();
  return 0;
}
