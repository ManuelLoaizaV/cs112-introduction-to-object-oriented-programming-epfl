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
  const Produit* adapter(double) const;
  double quantiteTotale(const string&) const;
};

Produit::Produit(string _nombre, string _unidad = "")
: nombre(_nombre), unidad(_unidad) {}

string Produit::getNom() const { return nombre; }

string Produit::getUnite() const { return unidad; }

string Produit::toString() const { return getNom(); }

const Produit* Produit::adapter(double n = 0.0) const { return this; }

double Produit::quantiteTotale(const string& nombre_producto) const {
  if (nombre == nombre_producto) return 1.0;
  else return 0.0;
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

Ingredient::Ingredient(const Produit& _producto, double _cantidad = 0.0)
: producto(_producto), cantidad(_cantidad) {}

const Produit& Ingredient::getProduit() const { return producto; }

double Ingredient::getQuantite() const { return cantidad; }

string Ingredient::descriptionAdaptee() const {
  string ans = "";
  ans = to_string(cantidad) + " " + producto.getUnite() + " de " + producto.toString();
  return ans;
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
  Recette adapter(double);
  string toString() const;
  double quantiteTotale(const string&) const;
};

Recette::Recette(string _nombre, double _factor = 1.0)
: nombre_receta(_nombre), factor(_factor) {}

void Recette::ajouter(const Produit& producto, double cantidad) {
  ingredientes.push_back(Ingredient(producto, factor * cantidad));
}

Recette Recette::adapter(double n) {
  Recette ans(nombre_receta, factor * n);
  int sz = ingredientes.size();
  for (int i = 0; i < sz; i++) ans.ajouter(ingredientes[i].getProduit(), n);
  return ans;
}

string Recette::toString() const {
  string ans = "Recette \"" + nombre_receta + "\" x " + to_string(factor) + ":\n";
  int sz = ingredientes.size();
  for (int i = 0; i < sz; i++) {
    ans += to_string(i + 1) + ". " + ingredientes[i].descriptionAdaptee();
    if (i < sz - 1) ans += '\n';
  }
  return ans;
};

double Recette::quantiteTotale(const string& nombre_producto) const {
  int sz = ingredientes.size();
  double ans = 0.0;
  for (int i = 0; i < sz; i++) {
    if (nombre_producto == ingredientes[i].getProduit().getNom()) {
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
  const ProduitCuisine* adapter(double);
  virtual string toString() const;
  double quantiteTotale(const string&) const;
};

ProduitCuisine::ProduitCuisine(string _nombre)
: Produit(_nombre, "portion (s)"), receta(_nombre) {}

void ProduitCuisine::ajouterARecette(const Produit& producto, double cantidad) {
  receta.ajouter(producto, cantidad);
}

const ProduitCuisine* ProduitCuisine::adapter(double n) {
  receta = receta.adapter(n);
  return this;
}

string ProduitCuisine::toString() const {
  string ans = Produit::toString() + '\n' + receta.toString();
  return ans;
}

double ProduitCuisine::quantiteTotale(const string& nombre_producto) const {
  if (Produit::getNom() == nombre_producto) return 1.0;
  return receta.quantiteTotale(nombre_producto);
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
