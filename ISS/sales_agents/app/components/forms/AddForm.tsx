import { FormType } from "@/types/FormType";
import { Product } from "@/types/Product";
import { User } from "@/types/User";
import { useState } from "react";
import Button from "../Button";
import { Bounce, toast } from "react-toastify";
import { BASE_URL } from "@/types/constants";

interface AddFormProps {
  user: User;
  setFormType: React.Dispatch<React.SetStateAction<FormType>>;
}

const AddForm: React.FC<AddFormProps> = ({ user, setFormType }) => {
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
  
  const [productData, setProductData] = useState<Product>({id: 0, name: '', quantity: 0, price: 0})

  const handleAddProduct = () => {
    if (productData.name.length === 0) {
      notify('Name cannot be empty')
      return
    } else if (productData.price === 0) {
      notify('Price cannot be 0')
      return
    }
    fetch(`${BASE_URL}/product/add?email=${user.email}&password=${user.password}`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Access-Control-Allow-Origin': '*'
      },
      body: JSON.stringify({
        name: productData.name,
        quantity: productData.quantity,
        price: productData.price
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
      <p className="text-black font-bold text-2xl mb-2">Add Product</p>
      <p className="text-black">Are you sure you want to add this product?</p>
      <div className="space-y-3 mt-4 flex flex-col items-center">
        <input
          value={productData.name}
          placeholder="Name"
          onChange={(e) => { e.target.value.length !== 0 ? setProductData({ ...productData, name: e.target.value }) : null }}
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
        <input
          value={productData.quantity}
          onChange={(e) => { /^\d+$/.test(e.target.value) ? setProductData({ ...productData, quantity: +e.target.value }) : null }}
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
        <input
          value={productData.price}
          onChange={(e) => { /^\d+$/.test(e.target.value) ? setProductData({ ...productData, price: +e.target.value }) : null }}
          className='border w-60 border-gray-300 bg-white text-black h-10 px-4 pr-10 rounded-lg focus:outline-none'
        />
      </div>
      <div className="flex justify-center space-x-4 mt-5">
        <Button
          label="Add"
          onClick={() => handleAddProduct()}
          width="5rem"
        />
        <Button
          label="Cancel"
          onClick={() => setFormType(FormType.NONE)}
          width="5rem"
        />
      </div>
    </div>
  );
}

export default AddForm;