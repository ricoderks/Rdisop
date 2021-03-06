#ifndef IMS_WEIGHTS_H
#define IMS_WEIGHTS_H

#include <vector>
#include <ostream>

namespace ims {

/**
 * @brief Represents a set of weights (double values and scaled with a certain
 * precision their integer counterparts) with a quick access.
 *
 * Many algorithms can't work with real-valued alphabets and need integer
 * weights. Those are usually obtained by dividing all alphabet masses by
 * a "precision" parameter (0; 1) and rounding the result to integers.
 * Class @c Weights allows access to the scaled masses (the weights) and to the
 * original masses as well. Weights are cached and will not be recalculated on
 * access.
 *
 * @note Words 'weights' and 'masses' were used deliberately for naming
 * corresponding values to help users quickly understand how they can be used.
 * Names were chosen due to similarity in 'weights' and 'masses' interconnection
 * in this class with real life. In reality mass value is always the same, and
 * weight value depends on circumstances. The same as here original double
 * masses stay the same, and scaled integer weights depend on precision applied.
 *
 * @author Anton Pervukhin <Anton.Pervukhin@CeBiTec.Uni-Bielefeld.DE>
 *
 * @ingroup alphabet
 */
class Weights {
	public:
		/**
		 * Type of integer values to be used.
		 */
		typedef long unsigned int weight_type;

		/**
		 * Type of double values to be used.
		 */
		typedef double alphabet_mass_type;

		/**
		 * Type of container to store integer values.
		 */
		typedef std::vector<weight_type> weights_type;

		/**
		 * Type of container to store double values.
		 */
		typedef std::vector<alphabet_mass_type> alphabet_masses_type;

		/**
		 * Type of container's size
		 */
		typedef weights_type::size_type size_type;

		/**
		 * Empty constructor.
		 */
		Weights() { }

		
		/**
		 * Constructor with double values and precision.
		 *
		 * @param masses Original double values to be scaled.
		 * @param precision Precision to scale double values.
		 */
		Weights(const alphabet_masses_type& masses, alphabet_mass_type precision);

		/**
		 * Copy constructor.
		 *
		 * @param other Weights to be copied.
		 */
		Weights(const Weights& other) :
			alphabet_masses(other.alphabet_masses),
			precision(other.precision),
			weights(other.weights) { }

		/**
		 * Assignment operator.
		 *
		 * @param weights Weights to be assigned.
		 * @return Reference to this object.
		 */
		Weights& operator =(const Weights& weights);

		/**
		 * Gets size of a set of weights.
		 *
		 * @return Size of a set of weights.
		 */
		size_type size() const { return weights.size(); }

		/**
		 * Gets a scaled integer weight by index.
		 *
		 * @param i An index to access weights.
		 * @return An integer weight.
		 */
		weight_type getWeight(size_type i) const { return weights[i]; }

		/**
		 * Sets a new precision to scale double values to integer.
		 *
		 * @param precision A new precision.
		 */
		void setPrecision(alphabet_mass_type precision);

		/**
		 * Gets precision.
		 *
		 * @return Precision to scale double values to integer.
		 */
		alphabet_mass_type getPrecision() const { return precision; }

		/**
		 * Operator to access weights by index.
		 *
		 * @param i An index to access weights.
		 * @return An integer weight.
		 *
		 * @see getWeight(size_type i)
		 */
		weight_type operator [](size_type i) const { return weights[i]; }

		/**
		 * Gets a last weight.
		 *
		 * @return a last weight.
		 */
		weight_type back() const { return weights.back(); }

		/**
		 * Gets an original (double) alphabet mass by index.
		 *
		 * @param i An index to access alphabet masses.
		 * @return A double alphabet mass.
		 */
		alphabet_mass_type getAlphabetMass(size_type i) const
									{ return alphabet_masses[i]; }

		/**
		 * Exchanges weight and mass at index1 with weight and mass at index2.
		 *
		 * @param index1 Index of weight and mass to be exchanged.
		 * @param index2 Index of weight and mass to be exchanged.
		 */
		void swap(size_type index1, size_type index2);

		/**
		 * Divides the integer weights by their gcd. The precision is also 
		 * adjusted.
		 *
		 * @return true if anything was changed, that is, 
		 * 											if the gcd was &gt; 1.
		 *         false if the gcd was already 1 or there are less 
		 * 											than two weights.
		 */
		bool divideByGCD();

	private:
		/**
		 * Container to store original (double) alphabet masses.
		 */
		alphabet_masses_type alphabet_masses;

		/**
		 * Precision which is used to scale double values to integer.
		 */
		alphabet_mass_type precision;

		/**
		 * Container to store scaled integer weights.
		 */
		weights_type weights;
};

/**
 * Prints weights to the stream @c os.
 *
 * @param os Output stream to which weights are written.
 * @param weigths Weights to be written.
 */
std::ostream& operator<<(std::ostream& os, const Weights& weights);

} // namespace ims

#endif
