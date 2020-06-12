#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
class Auteur {
     private:
     string name;
     bool awarded;
     public:
     Auteur() = default;
     Auteur(string nombre, bool premiado = false)
     : name(nombre), awarded(premiado) {}
     string getNom() const;
     bool getPrix() const;
};

string Auteur::getNom() const { return name; }

bool Auteur::getPrix() const { return awarded; }

class Oeuvre {
     private:
     string title;
     // Puntero a un (Autor constante)
     // const Auteur* author;
     // (Puntero a un autor) constante
     // Auteur* const author;
     
     // En este caso quiero una referencia constante
     // Según https://stackoverflow.com/questions/7420780/what-is-a-constant-reference-not-a-reference-to-a-constant/7432351
     // toda referencia es constante, por lo cual usar const es redundante
     Auteur& author;
     string language;
     public:
     Oeuvre() = default;
     Oeuvre(Oeuvre const&) = delete;
     Oeuvre(string titulo, Auteur& autor, string idioma)
     : title(titulo), author(autor), language(idioma) {}
     ~Oeuvre() {
          cout << "L'oeuvre \"" << title
          << ", " << author.getNom()
          << ", en " << language
          << "\" n'est plus disponible." << endl;
     }
     string getTitre() const;
     Auteur& getAuteur() const;
     string getLangue() const;
     void affiche() const;
};

string Oeuvre::getTitre() const { return title; }

Auteur& Oeuvre::getAuteur() const { return author; }

string Oeuvre::getLangue() const { return language; }

void Oeuvre::affiche() const {
     cout << title << ", " << author.getNom() << ", en " << language << endl;
}

class Exemplaire {
     private:
     Oeuvre& book;
     public:
     Exemplaire() = default;
     Exemplaire(Oeuvre& obra) : book(obra) { 
          cout << "Nouvel exemplaire de : " <<  book.getTitre()
          << ", " << book.getAuteur().getNom()
          << ", en " << book.getLangue() << endl;
     }
     Exemplaire(Exemplaire& otro) : book(otro.getOeuvre()) {
          cout << "Copie d'un exemplaire de : " <<  book.getTitre()
          << ", " << book.getAuteur().getNom()
          << ", en " << book.getLangue() << endl;
     }
     ~Exemplaire() {
          cout << "Un exemplaire de \"" <<  book.getTitre()
          << ", " << book.getAuteur().getNom()
          << ", en " << book.getLangue()
          << "\" a été jeté !" << endl;
     }
     Oeuvre& getOeuvre() const;
     void affiche() const;
};

Oeuvre& Exemplaire::getOeuvre() const { return book; }

void Exemplaire::affiche() const {
     cout << "Exemplaire de : " <<  book.getTitre()
     << ", " << book.getAuteur().getNom()
     << ", en " << book.getLangue() << endl; 
}

class Bibliotheque {
     private:
     string name;
     // Esto no me compilaba porque solo puedes crear un vector de cosas asignables
     // https://stackoverflow.com/questions/922360/why-cant-i-make-a-vector-of-references
     // vector<Exemplaire&> library;
     vector<Exemplaire*> library;
     public:
     Bibliotheque() = default;
     Bibliotheque(string nombre) : name(nombre)
     { cout << "La bibliothèque " << name << " est ouverte !" << endl; }
     
     string getNom() const;
     void stocker(Oeuvre&, int);
     void lister_exemplaires() const;
     void lister_exemplaires(string) const;
     int compter_exemplaires(Oeuvre&) const;
     void afficher_auteurs(bool) const;
     
     ~Bibliotheque() {
          cout << "La bibliothèque " << name << " ferme ses portes,"
          << endl << "et détruit ses exemplaires :" << endl;
          // Para invocar al destructor, debo usar la palabra delete
          // https://stackoverflow.com/questions/4036394/how-do-i-call-the-classs-destructor
          int sz = library.size();
          for (int i = 0; i < sz; i++) delete library[i];
     }
};

string Bibliotheque::getNom() const { return name; }

void Bibliotheque::stocker(Oeuvre& obra, int times = 1) {
     while (times--) {
          // Para obtener dirección de memoria dinámica de un objeto necesito usar new
          // https://stackoverflow.com/questions/25088801/c-dynamic-memory-allocation-using-new
          Exemplaire* ejemplar = new Exemplaire(obra);
          library.push_back(ejemplar);
     }
}

void Bibliotheque::lister_exemplaires() const {
     int sz = library.size();
     for (int i = 0; i < sz; i++) (*library[i]).affiche();
}

void Bibliotheque::lister_exemplaires(string idioma) const {
     int sz = library.size();
     for (int i = 0; i < sz; i++) {
          if ((*library[i]).getOeuvre().getLangue() == idioma) (*library[i]).affiche();
     }
}

int Bibliotheque::compter_exemplaires(Oeuvre& obra) const {
     int sz = library.size();
     int cnt = 0;
     for (int i = 0; i < sz; i++) {          
          if ( (*library[i]).getOeuvre().getTitre() == obra.getTitre() and
               (*library[i]).getOeuvre().getAuteur().getNom() == obra.getAuteur().getNom() and
               (*library[i]).getOeuvre().getLangue() == obra.getLangue() ) cnt++;
     }
     return cnt;
}

void Bibliotheque::afficher_auteurs(bool prize = false) const {
     int sz = library.size();
     for (int i = 0; i < sz; i++) {
          string name = (*library[i]).getOeuvre().getAuteur().getNom();
          if (prize) {
               if ((*library[i]).getOeuvre().getAuteur().getPrix()) {
                    cout << name << endl;
               }
          } else {
               cout << name << endl;
          }
     }
}

/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
