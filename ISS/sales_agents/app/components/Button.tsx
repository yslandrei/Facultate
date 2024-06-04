import React from 'react';

interface IButtonProps {
  label: string;
  width: string;
  onClick: () => void;
}

const Button: React.FC<IButtonProps> = ({ label, width, onClick }) => {
  return (
    <button 
      className={`bg-blue-500 h-min text-white p-2 rounded-md`}
      style={{'width': width}}
      onClick={onClick}
    >
      {label}
    </button>

  );
};

export default Button;