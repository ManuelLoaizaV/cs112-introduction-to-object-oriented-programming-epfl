#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
class Produit {
protected:
  string nombre;
  string unidad;
public:
  Produit(string, string);
  string getNom() const;
  string getUnite() const;
  virtual string toString() const;
  virtual const Produit* adapter(double) const;
  virtual double quantiteTotale(const string&) const;
};

Produit::Produit(string _nombre, string _unidad = "")
: nombre(_nombre), unidad(_unidad) {}

string Produit::getNom() const { return nombre; }

string Produit::getUnite() const { return unidad; }

string Produit::toString() const { return nombre; }

const Produit* Produit::adapter(double n) const { return this; }

double Produit::quantiteTotale(const string& nombre_producto) const {
  if (nombre == nombre_producto) return 1;
  return 0;
}

class Ingredient {
protected:
  const Produit& producto;
  double cantidad;
public:
  Ingredient(const Produit&, double);
  const Produit& getProduit() const;
  double getQuantite() const;
  string descriptionAdaptee() const;
  double quantiteTotale(const string&) const;
};

Ingredient::Ingredient(const Produit& _producto, double _cantidad)
: producto(_producto), cantidad(_cantidad) {}

const Produit& Ingredient::getProduit() const { return producto; }

double Ingredient::getQuantite() const { return cantidad; }

string Ingredient::descriptionAdaptee() const {
  stringstream ss;
  const Produit* p = producto.adapter(cantidad);
  ss << cantidad << " " << producto.getUnite() << " de " << p->toString();
  return ss.str();
}

double Ingredient::quantiteTotale(const string& nombre_producto) const {
  return cantidad * producto.quantiteTotale(nombre_producto);
}

class Recette {
protected:
  vector<Ingredient> ingredientes;
  string nombre_receta;
  double factor;
public:
  Recette(string, double);
  void ajouter(const Produit&, double);
  Recette adapter(double) const;
  string toString() const;
  double quantiteTotale(const string&) const;
};

Recette::Recette(string _nombre, double _factor = 1.0)
: nombre_receta(_nombre), factor(_factor) {}

void Recette::ajouter(const Produit& producto, double cantidad) {
  Ingredient temp(producto, factor * cantidad);
  ingredientes.push_back(temp);
}

//TODO
Recette Recette::adapter(double n) const {
  Recette ans(nombre_receta, factor * n);
  int sz = ingredientes.size();
  for (int i = 0; i < sz; i++) {

  }
  return ans;
}

string Recette::toString() const {
  stringstream ss;
  ss << "Recette \"" << nombre_receta << "\" x " << factor << ":" << endl;
  int sz = ingredientes.size();
  for (int i = 0; i < sz; i++) {
    ss << i + 1 << ". " << ingredientes[i].descriptionAdaptee();
    if (i < sz - 1) ss << endl;
  }
  return ss.str();
};

// El compilador tiene que estar seguro que no modificaremos 'const Recette' del main
// https://stackoverflow.com/questions/5973427/error-passing-xxx-as-this-argument-of-xxx-discards-qualifiers
double Recette::quantiteTotale(const string& nombre_producto) const {
  double ans = 0.0;
  int sz = ingredientes.size();
  for (int i = 0; i < sz; i++) {
    if (ingredientes[i].getProduit().getNom() == nombre_producto) {
      ans += ingredientes[i].getQuantite();
    }
  }
  return ans;
}

class ProduitCuisine : public Produit {
protected:
  Recette receta;
public:
  ProduitCuisine(string);
  void ajouterARecette(const Produit&, double);
  const Produit* adapter(double) const override;
  virtual string toString() const override;
  virtual double quantiteTotale(const string&) const override;
};

ProduitCuisine::ProduitCuisine(string _nombre)
: Produit(_nombre, "portion (s)"), receta(_nombre) {}

void ProduitCuisine::ajouterARecette(const Produit& producto, double cantidad) {
  receta.ajouter(producto, cantidad);
}

const Produit* ProduitCuisine::adapter(double n) const{
  receta.adapter(n);
  return this;
}

string ProduitCuisine::toString() const{
  stringstream ss;
  ss << Produit::toString() << endl << receta.toString();
  return ss.str();
}

double ProduitCuisine::quantiteTotale(const string& nombre_producto) const {
  if (nombre == nombre_producto) return 1;
  else return receta.quantiteTotale(nombre_producto);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
}
