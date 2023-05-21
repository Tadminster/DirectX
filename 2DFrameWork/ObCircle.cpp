#include "framework.h"
ID3D11Buffer* ObCircle::fillVertexBuffer = nullptr;
ID3D11Buffer* ObCircle::vertexBuffer = nullptr;

void ObCircle::CreateStaticMember()
{
    VertexPC* Vertex;
    Vertex = new VertexPC[360 * 3];

    for (UINT i = 0; i < 360; i++)
    {

        Vertex[i * 3].position.x = 0.0f;
        Vertex[i * 3].position.y = 0.0f;
        Vertex[i * 3].color = Color(1.f, 1.f, 1.0f, 1.0f);
        //Vertex[i * 3].color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);

        //0 1 2 ... 359
        Vertex[i * 3 + 1].position.x = cosf(i * ToRadian) * 0.5f;
        Vertex[i * 3 + 1].position.y = sinf(i * ToRadian) * 0.5f;
        //Vertex[i * 3 + 1].color = Color(0.f, 0.f, 0.f, 1.0f);
        //Vertex[i * 3 + 1].color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);

        //1 2 3 .. 360
        Vertex[i * 3 + 2].position.x = cosf((i + 1) * ToRadian) * 0.5f;
        Vertex[i * 3 + 2].position.y = sinf((i + 1) * ToRadian) * 0.5f;
        //Vertex[i * 3 + 2].color = Color(0.f, 0.f, 0.f, 1.0f);
        //Vertex[i * 3 + 2].color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);
          
        if (i < 60)
        {
            // red
            float color = i / 60.f;

            Vertex[i * 3 + 1].color = Color(1.f, 0.0f, 1.0f - color, 1.0f);
            Vertex[i * 3 + 2].color = Color(1.f, 0.0f, 1.0f - color, 1.0f);
        }
        else if (i < 120)
        {
            // Red to yellow
            float color = (i - 60) / 60.f;

            Vertex[i * 3 + 1].color = Color(1.0f, color, 0.0f, 1.0f);
            Vertex[i * 3 + 2].color = Color(1.0f, color, 0.0f, 1.0f);
        }
        else if (i < 180)
        {
            // Yellow to Green
            float color = (i - 120) / 60.f;

            Vertex[i * 3 + 1].color = Color(1.0f - color, 1.f, 0.0f, 1.0f);
            Vertex[i * 3 + 2].color = Color(1.0f - color, 1.f, 0.0f, 1.0f);
        }
        else if (i < 240)
        {
            // Green to cyan
            float color = (i - 180) / 60.f;

            Vertex[i * 3 + 1].color = Color(0.0f, 1.f, color, 1.0f);
            Vertex[i * 3 + 2].color = Color(0.0f, 1.f, color, 1.0f);
        }
        else if (i < 300)
        {
            // Cyan to blue
            float color = (i - 240) / 60.f;

            Vertex[i * 3 + 1].color = Color(0.0f, 1.f - color, 1.0f, 1.0f);
            Vertex[i * 3 + 2].color = Color(0.0f, 1.f - color, 1.0f, 1.0f);
        }
        else
        {
            // Blue to magenta
            float color = (i - 300) / 60.f;

            Vertex[i * 3 + 1].color = Color(color, 0.0f, 1.0f, 1.0f);
            Vertex[i * 3 + 2].color = Color(color, 0.0f, 1.0f, 1.0f);
        }
    }
    //�������� ���۷� �Ű����� �ڵ�
    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 }; //������� ���� 0����
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * 360 * 3; //���� ũ�� (����Ʈ)�Դϴ�.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���۰� ������ ���ο� ���ε��Ǵ� ����� �ĺ��Ͻʽÿ�

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //���� ���ҽ��� �ʱ�ȭ�ϱ����� �����͸� �����մϴ�.
        data.pSysMem = Vertex;
        //�ʱ�ȭ �������� ������.

        //���� �����
        //                                           ����    ����       ������   
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &fillVertexBuffer);
        assert(SUCCEEDED(hr));

    }

    delete[] Vertex;

    Vertex = new VertexPC[361];

    //�ΰ��� ������ �� �����
    for (UINT i = 0; i < 361; i++)
    {
        Vertex[i].color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        Vertex[i].position.x = cosf(i * ToRadian) * 0.5f;
        Vertex[i].position.y = sinf(i * ToRadian) * 0.5f;
    }


    {
        D3D11_BUFFER_DESC desc;
        desc = { 0 };
        desc.Usage = D3D11_USAGE_DEFAULT;//���۸� �а� ���� ���
        desc.ByteWidth = sizeof(VertexPC) * 361; //���� ũ�� (����Ʈ)�Դϴ�.
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���۰� ������ ���ο� ���ε��Ǵ� ����� �ĺ��Ͻʽÿ�

        D3D11_SUBRESOURCE_DATA data = { 0 };
        //���� ���ҽ��� �ʱ�ȭ�ϱ����� �����͸� �����մϴ�.
        data.pSysMem = Vertex;
        //�ʱ�ȭ �������� ������.

        //���� �����
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
        assert(SUCCEEDED(hr));

    }
    delete[] Vertex;
}

void ObCircle::DeleteStaticMember()
{
    vertexBuffer->Release();
    fillVertexBuffer->Release();
}

ObCircle::ObCircle()
{
    collider = COLLIDER::CIRCLE;
}

void ObCircle::Render()
{
    if (!isVisible)return;
    GameObject::Render();

    basicShader->Set();

    UINT stride = sizeof(VertexPC);
    UINT offset = 0;

    if (isFilled)
    {
        D3D->GetDC()->IASetVertexBuffers(0,
            1,
            &fillVertexBuffer,
            &stride,
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        D3D->GetDC()->Draw(360 * 3, 0);
    }
    else
    {
        D3D->GetDC()->IASetVertexBuffers(0,//�Է½���(16~32������ ��������)
            1,//�Է½��Կ� ���̰��� �ϴ� ������ ����
            &vertexBuffer,
            &stride,//���������� �� ������ ����Ʈ���� ũ��
            &offset);
        D3D->GetDC()->IASetPrimitiveTopology
        (D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
        D3D->GetDC()->Draw(361, 0);
    }
}
