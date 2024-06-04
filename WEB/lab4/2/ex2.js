const setOkStyle = (input) => {
    input.className = 'ok-input';
}
const validateName = (name) => {
    if (name.length < 5) {
        return 'Campul numelui trebuia sa aiba minim 5 caractere';
    }
    return '';
}
const validateBirthDate = (date) => {
    if (date === '') {
        return 'Campul datei nasterii nu poate fi gol';
    }
    return '';
}
const validateAge = (age) => {
    if (age === '') {
        return 'Campul varstei nu poate fi gol'
    }
    if (isNaN(age)) {
        return 'Campul varstei trebuie sa fie un numar';
    }
    return '';
}
const validateMail = (mail) => {
    const regex = /\S+@\S+\.\S+/;
    if (mail === '') {
        return 'Campul adresei de email nu poate fi goala';
    }
    if (!mail.match(regex)) {
        return 'Email-ul nu este valid';
    }
    return '';
}
const handleFormButtonPressed = () => {
    const nameInput = document.getElementById('nameInput');
    const birthInput = document.getElementById('birthInput');
    const ageInput = document.getElementById('ageInput');
    const mailInput = document.getElementById('mailInput');

    const inputValidators = {
        name: {
            input: nameInput,
            validator: validateName
        },
        birth: {
            input: birthInput,
            validator: validateBirthDate
        },
        age: {
            input: ageInput,
            validator: validateAge
        },
        mail: {
            input: mailInput,
            validator: validateMail
        }
    }

    let errors = '';
    let err;

    for (const key in inputValidators) {
        const inputValidator = inputValidators[key];
        if ((err = inputValidator.validator(inputValidator.input.value)) !== '') {
            errors += err + '\n';
            inputValidator.input.className = 'invalid-input';
        }
    }

    if (errors !== '') {
        errors.slice(0, -1);
        alert(errors);
    }
    else {
        alert('Form-ul a fost trimis');
    }
}