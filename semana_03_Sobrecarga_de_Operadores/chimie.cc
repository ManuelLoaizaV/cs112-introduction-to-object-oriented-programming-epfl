#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Flacon() = delete;
  Flacon(string, double, double);
  ostream& etiquette(ostream&) const;
  Flacon operator+=(Flacon const&);
};

Flacon::Flacon(string nombre, double volumen, double ph)
: nom(nombre), volume(volumen), pH(ph) {}

ostream& Flacon::etiquette(ostream& sortie) const {
  sortie << nom << " : " << volume << " ml, pH " << pH;
  return sortie;
}

ostream& operator<<(ostream& sortie, Flacon const& f) {
  return f.etiquette(sortie);
}

#define BONUS
Flacon Flacon::operator+=(Flacon const& otro) {
  nom = nom + " + " + otro.nom;
  double num = volume * pow(10.0, -pH) + otro.volume * pow(10.0, -otro.pH);
  volume += otro.volume;
  pH = -log10(num / volume);
  return *this;
}

Flacon operator+(Flacon f1, Flacon const& f2) {
  f1 += f2;
  return f1;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
