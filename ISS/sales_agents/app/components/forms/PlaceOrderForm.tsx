import { FormType } from "@/types/FormType";
import { Product } from "@/types/Product";
import { User } from "@/types/User";
import { useState } from "react";
import { Bounce, toast } from "react-toastify";
import Button from "../Button";
import { BASE_URL } from "@/types/constants";

interface PlaceOrderFormProps {
  user: User;
  product: Product
  setFormType: React.Dispatch<React.SetStateAction<FormType>>;
}

const PlaceOrderForm: React.FC<PlaceOrderFormProps> = ({ user, product, setFormType }) => {
  const notify = (error: string) => toast.error(error, {
    position: "top-right",
    autoClose: 5000,
    hideProgressBar: false,
    closeOnClick: true,
    pauseOnHover: true,
    draggable: true,
    progress: undefined,
    theme: "dark",
    transition: Bounce,
  });

  const [quantity, setQuantity] = useState(1);

  const handlePlaceOrder = () => {
    fetch(`${BASE_URL}/product/place?email=${user.email}&password=${user.password}`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Access-Control-Allow-Origin': '*'
      },
      body: JSON.stringify({
        productId: product.id,
        quantity: quantity
      })
    }).then(response => {
      if (response.ok) {
        setFormType(FormType.NONE)
      } else {
        response.text().then(text => notify(text))
      }
    })
  }

  return (
    <div className="flex flex-col items-center justify-center">
      <p className="text-black font-bold text-2xl mb-2">Place Order</p>
      <p className="text-black">Are you sure you want to place this order?</p>
      <div className="space-y-3 mt-4 flex flex-col items-center">
        <input
          value={product.name}
          readOnly
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
        <input
          value={product.quantity}
          readOnly
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
        <input
          value={product.price}
          readOnly
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
      </div>
      <div className="flex items-center mt-4">
        <button
          onClick={() => setQuantity(prev => prev - 1 > 0 ? prev - 1 : prev)}
          className="px-4 py-2 bg-blue-500 rounded-l-md border-y-blue-500 border-y-[1px]"
        >
          <p className='font-extrabold'>-</p>
        </button>
        <input
          type="text"
          value={quantity}
          onChange={(e) => isNaN(parseInt(e.target.value)) ? null : setQuantity(parseInt(e.target.value))}
          className="px-2 py-2 w-20 bg-white text-black text-center focus:outline-none border-y-blue-500 border-y-[1px]"
        />
        <button
          onClick={() => setQuantity(prev => prev + 1)}
          className="px-4 py-2 bg-blue-500 rounded-r-md border-y-blue-500 border-y-[1px]"
        >
          <p className='font-extrabold'>+</p>
        </button>
      </div>
      <div className="flex justify-center space-x-4 mt-5">
        <Button
          label='Order'
          onClick={() => handlePlaceOrder()}
          width='5rem'
        />
        <Button 
          label = "Cancel"
          onClick = {() => setFormType(FormType.NONE)}
          width="5rem"
        />
      </div>
      
    </div>
  );
}

export default PlaceOrderForm;