#include "network.h"
#include "random.h"
#include <string>

    void Network::resize(const size_t& n) {
		values.resize(n);
		for (auto& val: values) {
			val = (RNG.normal(0,1)); 
		}
	}

    bool Network::add_link(const size_t& x, const size_t& y) {		  
		  std::vector<size_t> voisins;
		  voisins=neighbors(x);
		  if((x>=size()) or (y>=size()) or (x==y)) {
			  return false;
		  }
		  else {			 
			for(auto voisin : voisins){
				if(voisin==y){
					return false;
				}
			}
			links.insert({x,y});
			links.insert({y,x});
			return true;
		} 
	}

    size_t Network::random_connect(const double& deg) {
		links.clear(); 
		int degree(0);
		size_t count(0); 
		std::vector<int> valeurs;
		valeurs.push_back(0); 
		
		for (size_t i(0); i< size(); ++i) {
			degree = RNG.poisson(deg);
			if (degree>size()-1) {
				degree = size() -1;
			}
			int compteur (0);
			for (int j(0); j<degree; ++j) {
				do {
					RNG.uniform_int(valeurs, 0, size() -1); 
					++compteur; 
				}
				while (not add_link(i, valeurs[0]) and (compteur<size()-1)); 
				++count; 				
			}
		}
		return count; 
	}

    size_t Network::set_values(const std::vector<double>& nodes){
		if (nodes.size()==size()) {
			values.clear();
			for (int i(0); i<nodes.size(); ++i) {
				values[i]=(nodes[i]);				
			}
			return nodes.size(); 
		}
		if (nodes.size()<size()) {
			for(int i(0); i<nodes.size(); ++i) {
				values[i] =  (nodes[i]);			
			}
			return nodes.size(); 
		}
		else {
			for(int i(0); i< size(); ++i)  {
				values[i] = (nodes[i]); 				
			}
			return size(); 
		}
	}

    size_t Network::size() const{
		return values.size();
	}

    size_t Network::degree(const size_t &_n) const{
		return links.count(_n);		
	}

    double Network::value(const size_t &_n) const{
		if (size() > _n) {
			return values[_n];
		} else {throw std::string("l'indice ne correspond pas");}
	}

    std::vector<double> Network::sorted_values() const{
		std::vector<double> val (values);
		std::sort(val.begin(), val.end()); 
		std::reverse(val.begin(), val.end()); 
		return val; 
	}

    std::vector<size_t> Network::neighbors(const size_t& n) const{
		std::vector<size_t> mine;
		mine.clear();
		for (auto link : links) {
			if (link.first == n) { mine.push_back(link.second);}
		}		
		return mine;
	}
