#include <iostream>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/
class Patient {
  private:
  double masse, hauteur;
  public:
  void init(double masa, double altura) {
    if (masa < 0 or altura < 0) {
      masse = hauteur = 0;
    } else {
      masse = masa;
      hauteur = altura;
    }
  }
  void afficher() {
    cout << "Patient : " << masse << " kg pour " << hauteur << " m" << endl;
  }
  double poids() { return masse; }
  double taille() { return hauteur; }
  double imc() {
    if (hauteur == 0) return 0;
    return masse / (hauteur * hauteur);
  }
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Patient quidam;
  double poids, taille;
  do {
    cout << "Entrez un poids (kg) et une taille (m) : ";
    cin >> poids >> taille;
    quidam.init(poids, taille);
    quidam.afficher();
    cout << "IMC : " << quidam.imc() << endl;
  } while (poids * taille != 0.0);
  return 0;
}
