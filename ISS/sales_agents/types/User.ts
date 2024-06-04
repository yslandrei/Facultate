export interface User {
  id: number;
  name: string;
  email: string;
  password: string;
  role: RoleType;
}

export enum RoleType {
  ADMIN = 'ADMIN',
  SALES_AGENT = 'SALES_AGENT',
}