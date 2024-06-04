import React from 'react';

interface InputFieldProps {
  type?: string,
  input: string,
  placeholder: string,
  setInput: React.Dispatch<React.SetStateAction<string>>
}

const InputField: React.FC<InputFieldProps> = ({ type, input, placeholder, setInput }) => {
  return (
    <input
      type={type}
      value={input || ''}
      placeholder={placeholder}
      className='border w-96 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
      onChange={(e) => setInput(e.target.value)}
    />
  );
};

export default InputField;