#!/bin/bash
# Détection du système
KERNEL_NAME=$(uname -s)
IS_WSL=$(uname -r | grep -i "microsoft" > /dev/null && echo "yes" || echo "no")
echo "Système détecté : $KERNEL_NAME"
# Cas 1 : Linux classique ou WSL
if [[ "$KERNEL_NAME" == "Linux" ]]; then
    if [[ "$IS_WSL" == "yes" ]]; then
        echo "(environnement WSL détecté)"
    fi
    if [ -f /proc/sys/kernel/pid_max ]; then
        echo -n "Limite maximale de PID : "
        cat /proc/sys/kernel/pid_max
    else
        echo "Impossible de lire /proc/sys/kernel/pid_max"
        echo "Peut-être que vous êtes sous WSL 1 ou que /proc n'est pas monté."
    fi
# Cas 2 : macOS
elif [[ "$KERNEL_NAME" == "Darwin" ]]; then
    echo "(environnement macOS détecté)"
    if command -v sysctl >/dev/null 2>&1; then
        echo -n "Limite max de processus : "
        sysctl -n kern.maxproc 2>/dev/null || echo "Indisponible"
        echo -n "Limite max par utilisateur : "
        sysctl -n kern.maxprocperuid 2>/dev/null || echo "Indisponible"
    else
        echo "La commande sysctl n’est pas disponible sur ce système."
    fi
# Cas inconnu
else
    echo "Système non reconnu. Script non compatible."
fi
