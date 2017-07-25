#pragma once
#include "constants.h"

class Pair;





class Atom
{
public:
	Atom();
	~Atom();
	

	int    id,
	       bond_id;
	char   atomtype[maxLine];
	int    frozen, 
	       adiabatic,
	       spectre, 
	       target;
	double mass,
	       charge,
	       polarizability,
	       epsilon, 
	       sigma,
	       omega,
	       c6,
	       c8,
	       c10,
	       c9,
	       es_self_point_energy,
	       pos[3],               // absolute position
	       wrapped_pos[3],       // wrapped (into main unit cell) position
	       ef_static[3],
	       ef_static_self[3],
	       ef_induced[3],
	       ef_induced_change[3],
	       mu[3],
	       old_mu[3],
	       new_mu[3],
	       dipole_rrms,
	       rank_metric,
	       gwp_alpha,
	       lrc_self,
	       last_volume;
	int    gwp_spin,
	       site_neighbor_id; // dr fluctuations will be applied along the vector from this atom to the atom identified by this variable
	Pair   *pairs;
	Atom   *next;
};

