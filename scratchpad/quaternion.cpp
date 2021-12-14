struct Quaternion {
    float coeff[4][4];

    inline Quaternion operator*(Quaternion other) {
        Quaternion mult = {
            .coeff = {
                {},
                {},
                {},
                {},
            }
        };

        return mult;
    }
};