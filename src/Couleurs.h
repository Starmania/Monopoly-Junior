//
// Created by romain on 23/05/25.
//

#ifndef COULEURS_H
#define COULEURS_H

namespace Couleur { // Pour rendre le Couleur::to_string explicite
    enum Couleur {
        VIOLET,
        BLANC,
        ROSE,
        ORANGE,
        ROUGE,
        JAUNE,
        VERT,
        BLEU
    };

    inline const char *to_string(Couleur e) {
        switch (e) {
            case VIOLET: return "VIOLET";
            case BLANC: return "BLANC";
            case ROSE: return "ROSE";
            case ORANGE: return "ORANGE";
            case ROUGE: return "ROUGE";
            case JAUNE: return "JAUNE";
            case VERT: return "VERT";
            case BLEU: return "BLEU";
            default: return "unknown";
        }
    }
}

#endif //COULEURS_H
