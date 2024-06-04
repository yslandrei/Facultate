import { Product } from "@/types/Product";
import Button from "../Button";
import { User } from "@/types/User";
import { FormType } from "@/types/FormType";
import { BASE_URL } from "@/types/constants";
import { Bounce, toast } from "react-toastify";

interface DeleteFormProps {
  user: User;
  product: Product
  setFormType: React.Dispatch<React.SetStateAction<FormType>>;
}

const DeleteForm: React.FC<DeleteFormProps> = ({ user, product, setFormType }) => {
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

  const handleDeleteProduct = (id: number) => {
    fetch(`${BASE_URL}/product/delete?email=${user.email}&password=${user.password}&id=${id}`, {
      method: 'DELETE',
      headers: {
        'Content-Type': 'application/json',
        'Access-Control-Allow-Origin': '*'
      }
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
      <p className="text-black font-bold text-2xl mb-2">Delete Product</p>
      <p className="text-black">Are you sure you want to delete this product?</p>
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
      <div className="flex justify-center space-x-4 mt-5">
        <Button 
          label = "Delete"
          onClick = {() => handleDeleteProduct(product.id)}
          width="5rem"
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

export default DeleteForm;