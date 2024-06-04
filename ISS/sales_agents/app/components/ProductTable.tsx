'use client'
import { Product } from "@/types/Product";
import { ProductFilters, SortType } from "@/types/ProductFilters";
import { RoleType, User } from "@/types/User";
import ProductActions from "./ProductActions";
import { FormType } from "@/types/FormType";
import { useState } from "react";
import { MdAdd, MdClose } from "react-icons/md";
import AddForm from "./forms/AddForm";
import ModifyForm from "./forms/ModifyForm";
import DeleteForm from "./forms/DeleteForm";
import PlaceOrderForm from "./forms/PlaceOrderForm";

interface ProductTableProps {
  products: Product[];
  user: User;
  filters: ProductFilters;
  setFilters: React.Dispatch<React.SetStateAction<ProductFilters>>;
}

const ProductTable: React.FC<ProductTableProps> = ({ products, user, filters, setFilters }) => {
  const [formType, setFormType] = useState<FormType>(FormType.NONE);
  const [selectedProduct, setSelectedProduct] = useState<undefined | Product>();

  const handleChangeSort = (column: string) => {
    if (column === 'name') {
      if (filters.sortType === SortType.ASC_NAME) {
        setFilters({ ...filters, sortType: SortType.DESC_NAME })
      } else if (filters.sortType === SortType.DESC_NAME) {
        setFilters({ ...filters, sortType: SortType.NONE })
      } else {
        setFilters({ ...filters, sortType: SortType.ASC_NAME })
      }
    } else if (column === 'quantity') {
      if (filters.sortType === SortType.ASC_QUANTITY) {
        setFilters({ ...filters, sortType: SortType.DESC_QUANTITY })
      } else if (filters.sortType === SortType.DESC_QUANTITY) {
        setFilters({ ...filters, sortType: SortType.NONE })
      } else {
        setFilters({ ...filters, sortType: SortType.ASC_QUANTITY })
      }
    } else if (column === 'price') {
      if (filters.sortType === SortType.ASC_PRICE) {
        setFilters({ ...filters, sortType: SortType.DESC_PRICE })
      } else if (filters.sortType === SortType.DESC_PRICE) {
        setFilters({ ...filters, sortType: SortType.NONE })
      } else {
        setFilters({ ...filters, sortType: SortType.ASC_PRICE })
      }
    }
  }

  return <>
    <table className="w-full">
      <thead className="bg-blue-500">
        <tr>
          <th className="px-4 py-3 w-96 relative left-2 cursor-pointer" onClick={() => handleChangeSort('name')}>Product Name {filters.sortType == SortType.ASC_NAME ? '↑' : filters.sortType == SortType.DESC_NAME ? '↓' : '  '}</th>
          <th className="px-4 py-3 w-32 relative left-2 cursor-pointer" onClick={() => handleChangeSort('quantity')}>Quantity {filters.sortType == SortType.ASC_QUANTITY ? '↑' : filters.sortType == SortType.DESC_QUANTITY ? '↓' : '  '}</th>
          <th className="px-4 py-3 w-32 relative left-2 cursor-pointer" onClick={() => handleChangeSort('price')}>Price {filters.sortType == SortType.ASC_PRICE ? '↑' : filters.sortType == SortType.DESC_PRICE ? '↓' : '  '}</th>
          <th className="px-4 py-3 w-32 relative left-6">
            <div className="flex items-center space-x-3">
              <p>Actions</p>
              {user.role === RoleType.ADMIN && <MdAdd
                onClick={() => setFormType(FormType.ADD)}
                className="w-5 h-5 cursor-pointer"
              />}
            </div>
          </th>
        </tr>
      </thead>
      <tbody className='bg-white  '>
        {products.map((product, index) => (
          <tr className='rounded-xl' key={index}>
            <td className="border px-4 py-3 text-black">{product.name}</td>
            <td className="border px-4 py-3 text-black text-center">{product.quantity}</td>
            <td className="border px-4 py-3 text-black text-center">${product.price}</td>
            <td className="border px-4 py-3 text-black text-center">
              <ProductActions
                user={user}
                product={product}
                setFormType={setFormType}
                setSelectedProduct={setSelectedProduct}
              />
            </td>
          </tr>
        ))}
        {products.length < 8 && [...Array(8 - products.length)].map((_, index) => (
          <tr className='rounded-xl' key={index}>
            <td className="border px-4 py-3 text-black"> </td>
            <td className="border px-4 py-3 text-black text-center"> </td>
            <td className="border px-4 py-3 text-black text-center"> </td>
            <td className="border px-4 py-3 text-black text-center"> </td>
          </tr>
        ))}
      </tbody>
    </table>

    {formType !== FormType.NONE && <>
      <div className="fixed bg-black w-full h-full left-0 top-0 opacity-50 z-10" />
      <div className="fixed w-full h-full top-0 left-0 flex justify-center items-center z-50" >
        <div className='bg-white rounded-md w-[20%] px-2 pt-4 pb-6'>
          {formType === FormType.ADD &&
            <AddForm
              user={user}
              setFormType={setFormType}
            />
          }
          {formType === FormType.MODIFY &&
            <ModifyForm
              user={user}
              product={selectedProduct!}
              setFormType={setFormType}
            />
          }
          {formType === FormType.DELETE &&
            <DeleteForm
              user={user}
              product={selectedProduct!}
              setFormType={setFormType}
            />
          }
          {formType === FormType.PLACE_ORDER &&
            <PlaceOrderForm
              user={user}
              product={selectedProduct!}
              setFormType={setFormType}
            />
          }
        </div>
      </div>
    </>}
  </>
}

export default ProductTable;