
    while (elevio_obstruction() == 1) { //ser etter obstruksjon
        
    }
    nanosleep(&(struct timespec){3, 0}, NULL);
    elevio_doorOpenLamp(0); //holder døren åpen i 3sek og lukker etterpå
}

//legg til openDoor i relevante filer